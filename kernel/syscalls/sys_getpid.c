#include <mach-context.h>
#include <micronix/schedule.h>
#include <micronix/process.h>

void sys_getpid( struct process_context* current_context ){
    struct pcb* current_pcb = scheduler_current_process();

    PROCESS_CONTEXT_RETVAL(current_pcb->pid,current_context);
}
