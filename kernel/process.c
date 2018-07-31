#include <micronix/process.h>
#include <micronix/klist.h>
#include <micronix/string.h>
#include <micronix/errno.h>
#include <generated/autoconf.h>
#include <micronix/panic.h>
#include <mach-context.h>
#include <micronix/stack.h>

#ifdef CONFIG_STATIC_PROCESS_LIST
static struct pcb all_pcbs[ CONFIG_MAX_STATIC_PROCESSES ];
static struct process_context all_context[ CONFIG_MAX_STATIC_PROCESSES ];
#else
#endif

static struct KList pcb_avail;
static struct pcb* currently_executing;
pid_t next_pid;
static struct KList sleeping_processes;
static struct KList reading_processes;
static struct KList waiting_processes;
static struct KList zombie_processes;
static struct KList context_avail;

static void process_context_init(void){
    int x;
    union KListKey key;

    klist_reset( &context_avail, NULL, NULL );

#ifdef CONFIG_STATIC_PROCESS_LIST
    key.ui = 0;
    for( x = 0; x < CONFIG_MAX_STATIC_PROCESSES; x++ ){
        klist_append( &context_avail, key, &all_context[ x ] );
        kmemset( &all_context[ x ], 0, sizeof(struct process_context) );
    }
#endif
}

static int process_context_allocate(struct process_context** context){
    int retval;

    if( context == NULL ||
        *context == NULL ){
        retval = -EINVAL;
        goto out;
    }

    retval = klist_pop_front( &context_avail, (void**)context );

out:
    return retval;
}

static int process_context_free(struct process_context* context){
    int retval;
    union KListKey key;

    if( context == NULL ){
        retval = -EINVAL;
        goto out;
    }

    key.ui = 0;
    kmemset(context, 0, sizeof(struct process_context) );
    retval = klist_append( &context_avail, key, context);

out:
    return retval;
}

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
    for( x = 0; x < CONFIG_MAX_STATIC_PROCESSES; x++ ){
        if( pcb_free( &all_pcbs[ x ] ) < 0 ){
            panic( "unable to init pcb" );
        }
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

    return ret + klist_append( &pcb_avail, key, NULL );
}

int pcb_alloc(struct pcb** pcb){
    int ret;
    if( !klist_empty( pcb_avail ) ){
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

    retval = pcb->pid;

out:
    return retval;
}
