#include <micronix/process.h>
#include <micronix/klist.h>
#include <micronix/string.h>
#include <micronix/errno.h>
#include <generated/autoconf.h>
#include <micronix/panic.h>

#ifdef CONFIG_STATIC_PROCESS_LIST
static struct pcb all_pcbs[ CONFIG_MAX_STATIC_PROCESSES ];
#else
#endif

static struct KList pcb_avail;
static struct pcb* currently_executing;
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
    
    if( tofree == NULL ){
        return -EINVAL;
    }
    key.ui = 0;
    kmemset( tofree, 0, sizeof( struct pcb ) );
    return klist_append( &pcb_avail, key, NULL );
}

int pcb_alloc(struct pcb** pcb){
    if( !klist_empty( pcb_avail ) ){
        return -ENOMEM;
    }

    return klist_pop_front( &pcb_avail, (void**)pcb );
}
