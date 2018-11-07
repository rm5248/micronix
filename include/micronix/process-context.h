#ifndef MICRONIX_PROCESS_CONTEXT_H
#define MICRONIX_PROCESS_CONTEXT_H

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
 * Set the PC(Program Counter) of the current context.
 */
void process_context_set_pc( struct process_context* context, int pc );

#endif
