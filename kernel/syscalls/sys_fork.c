#include <micronix/process.h>
#include <micronix/schedule.h>
#include <micronix/string.h>
#include <mach-context.h>
#include <stddef.h>

#include <micronix/printk.h>

void sys_fork( struct process_context* current_context ){
    struct pcb* new_pcb = NULL;
    int retval;

    retval = pcb_alloc( &new_pcb );
    if( retval ){
        goto out_err;
    }

    retval = stack_alloc( &(new_pcb->stack) );
    if( retval ){
        goto out_err;
    }
    new_pcb->pid = next_pid;
    new_pcb->ppid = scheduler_current_process()->pid;
    new_pcb->status = 0;
    new_pcb->sleeptime = 0;
    new_pcb->state = PROCESS_STATE_READY;

    kmemcpy( new_pcb->context, current_context, sizeof(struct process_context) );
    process_context_set_pc( new_pcb->context, PROCESS_CONTEXT_PC(current_context) );
    //process_context_set_stack( new_pcb->context, new_pcb->stack );

    /* Copy stack from current process to new process */
    kmemcpy( new_pcb->stack, scheduler_current_process()->stack, sizeof(stack_t) );

    /* Need to update stack pointer for new process */
    retval = process_context_fix_stack(scheduler_current_process(), new_pcb);
    if( retval ){
        goto out_err;
    }

    /* Make sure that the PC is set to our next instruction */
    process_context_increment_pc_after_syscall(new_pcb->context);

    retval = scheduler_schedule( new_pcb );
    if( retval ){
        goto out_err;
    }

    next_pid++;

    /* Tell parent PID of process */
    PROCESS_CONTEXT_RETVAL(new_pcb->pid,current_context);
    /* Tell child 0 */
    PROCESS_CONTEXT_RETVAL(0,new_pcb->context);
    return;

out_err:
    /* TODO properly cleanup here */
    PROCESS_CONTEXT_RETVAL(-1,current_context);
}
