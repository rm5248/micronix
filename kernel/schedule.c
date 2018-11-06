#include <micronix/schedule.h>
#include <micronix/klist.h>
#include <micronix/panic.h>
#include <micronix/process.h>
#include <micronix/string.h>
#include <mach-context.h>

static struct KList ready_processes;
static struct pcb* currently_executing;

void scheduler_init(){
    currently_executing = NULL;
    klist_reset( &ready_processes, NULL, NULL );
}

int scheduler_schedule( struct pcb* process ){
    union KListKey key;

    key.i = process->pid;

    return klist_append( &ready_processes, key, process );
}

int scheduler_dispatch(){
    /* Grab a new process off of our list of ready processes,
     * and start executing it
     */
    int ret = 0;

    if( ready_processes.length == 0 &&
        currently_executing == NULL ){
        /* PANIC */
        panic( "No processes to execute" );
    }

    /* 
     * Add our currently running process to our list of processes 
     * that are ready.  If we only have one process, this ensures
     * that we will continue to execute this process
     */
    scheduler_schedule( currently_executing );

    ret = klist_pop_front( &ready_processes, (void**)&currently_executing );

    return ret;
}

void scheduler_update_current_context(const struct process_context* context){
    kmemcpy( currently_executing->context, context, sizeof( struct process_context ) );
}

struct pcb* scheduler_current_process(){
    return currently_executing;
}
