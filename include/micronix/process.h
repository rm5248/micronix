#ifndef MICRONIX_PROCESS_H
#define MICRONIX_PROCESS_H

#include <micronix/compiler_types.h>
#include <micronix/stack.h>

#define INIT_PID 1

enum ProcessState{
    PROCESS_STATE_FREE = 0,
    PROCESS_STATE_NEW,
    PROCESS_STATE_READY,
    PROCESS_STATE_RUNNING,
    PROCESS_STATE_SLEEPING,
    PROCESS_STATE_BLOCKED,
    PROCESS_STATE_WAITING,
    PROCESS_STATE_KILLED,
    PROCESS_STATE_ZOMBIE,
    PROCESS_STATE_MAX
};

/* Contains the context(registers) of a process.
 * arch-dependent 
 */
struct process_context;

typedef uint32_t pid_t;
typedef uint32_t time_t;

struct pcb {
    struct process_context *context;       // ptr to process context
    stack_t                *stack;         // ptr to full stack
    pid_t                  pid;            // who we are
    pid_t                  ppid;           // who created us
    int32_t                status;         // termination status of this process
    time_t                 sleeptime;      // when the process started sleeping
    enum ProcessState      state;          // current process state
};

/**
 * Initialize the process subsystem
 */
void process_init(void);

/**
 * free the given pcb
 */
int pcb_free(struct pcb*);

/**
 * Allocate a new PCB.  If there are no PCBs, return an appropriate error code
 */
int pcb_alloc(struct pcb**);

/**
 * Create the first process.  This process will begin execution
 * after all initialization code and will not be running
 * in kernel mode but usermode(if available)
 */
int process_create_first(int (*main_function)(void) );

/*int process_context_*/

#endif
