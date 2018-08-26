#ifndef MICRONIX_SCHEDULE_H
#define MICRONIX_SCHEDULE_H

#include <micronix/process.h>

void scheduler_init(void);

/*
 * Schedule the given process.
 */
int scheduler_schedule( struct pcb* );

/*
 * Dispatch(run) the next available process.
 */
int scheduler_dispatch(void);

#endif
