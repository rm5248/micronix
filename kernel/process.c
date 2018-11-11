#include <micronix/process.h>
#include <micronix/klist.h>
#include <micronix/string.h>
#include <micronix/errno.h>
#include <generated/autoconf.h>
#include <micronix/panic.h>
#include <mach-context.h>
#include <micronix/stack.h>
#include <micronix/schedule.h>
#include <micronix/uart.h>
#include <micronix/process-context.h>
#include <stddef.h>

#include <coprocessor-regs.h>

#ifdef CONFIG_STATIC_PROCESS_LIST
static struct pcb all_pcbs[ CONFIG_MAX_STATIC_PROCESSES ];
#else
#endif

static struct KList pcb_avail;
pid_t next_pid;
static struct KList sleeping_processes;
static struct KList reading_processes;
static struct KList waiting_processes;
static struct KList zombie_processes;

void process_init(){
    int x;

    next_pid = INIT_PID + 1;

    klist_reset( &sleeping_processes, NULL, NULL );
    klist_reset( &reading_processes, NULL, NULL );
    klist_reset( &waiting_processes, NULL, NULL );
    klist_reset( &zombie_processes, NULL, NULL );
    klist_reset( &pcb_avail, NULL, NULL );

    process_context_init();

#ifdef CONFIG_STATIC_PROCESS_LIST
    kmemset( all_pcbs, 0, sizeof( all_pcbs ) );
    for( x = 0; x < CONFIG_MAX_STATIC_PROCESSES; x++ ){
        union KListKey key;
        key.ui = 0;

        klist_append( &pcb_avail, key, &all_pcbs[ x ] );
    }
#endif
}

int pcb_free(struct pcb* tofree){
    union KListKey key;
    int ret;
    
    if( tofree == NULL ){
        return -EINVAL;
    }
    key.ui = 0;

    ret = process_context_free( tofree->context );

    kmemset( tofree, 0, sizeof( struct pcb ) );

    return ret + klist_append( &pcb_avail, key, tofree );
}

int pcb_alloc(struct pcb** pcb){
    int ret;

    if( klist_empty( pcb_avail ) ){
        return -ENOMEM;
    }

    ret = klist_pop_front( &pcb_avail, (void**)pcb );
    if( ret ){
        return ret;
    }
    ret = process_context_allocate( &((*pcb)->context) );
    return ret;
}

int process_create_first(int (*main_function)(void) ){
    struct pcb* pcb;
    int retval;

    retval = pcb_alloc( &pcb );
    if( retval ){
        goto out;
    }

    retval = stack_alloc( &(pcb->stack) );
    if( retval ){
        goto out;
    }
    pcb->pid = INIT_PID;
    pcb->ppid = INIT_PID;
    pcb->status = 0;
    pcb->sleeptime = 0;
    pcb->state = PROCESS_STATE_READY;

    process_context_allocate( &(pcb->context) );
    process_context_set_pc( pcb->context, (int)main_function );
    process_context_set_stack( pcb->context, pcb->stack );

    retval = scheduler_schedule( pcb );
    if( retval ){
        goto out;
    }

    retval = pcb->pid;

out:
    return retval;
}
