#ifndef MICRONIX_SCHEDULE_H
#define MICRONIX_SCHEDULE_H

struct pcb;
struct process_context;

void scheduler_init(void);

/*
 * Schedule the given process.
 */
int scheduler_schedule( struct pcb* );

/*
 * Dispatch(run) the next available process.
 */
int scheduler_dispatch(void);

/*
 * Update the context for the currently running context.
 */
void scheduler_update_current_context( struct process_context* );

#endif
