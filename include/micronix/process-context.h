#ifndef MICRONIX_PROCESS_CONTEXT_H
#define MICRONIX_PROCESS_CONTEXT_H

#include <micronix/stack.h>

struct pcb;

/*
 * The functions defined in this file must be 
 * implemented for each architecture that the 
 * kernel is ported to.
 */

/*
 * Generic process_context struct. Implementation depends
 * on the actual architecture.
 */
struct process_context;

/**
 * Initialize our process context subsystem.
 */
void process_context_init( void );

/**
 * Set the PC(Program Counter) of the current context.
 */
void process_context_set_pc( struct process_context* context, int pc );

/**
 * Allocate a new process context
 */
int process_context_allocate( struct process_context** );

int process_context_free(struct process_context*);

int process_context_set_stack(struct process_context*, stack_t* stack );

/**
 * Fix the stack for the process after a fork.  Needed when we don't have
 * virtual memory.
 */
int process_context_fix_stack(const struct pcb* original, struct pcb* newproc);

/**
 * Increment the PC after the syscall(if required by the arch)
 */
int process_context_increment_pc_after_syscall(struct process_context* context);

#endif
