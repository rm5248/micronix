#ifndef MICRONIX_PROCESSOR_INIT_H
#define MICRONIX_PROCESSOR_INIT_H

/*
 * Contains function prototypes for processor
 * initialization
 */

/*
 * Called early in the boot process.  Should do any 
 * processor-specific initialization(such as setting up
 * clocks, copying data into RAM, etc)
 */
void processor_init(void);

/*
 * Initialize the interrupt controller on the processor,
 * but don't enable interrupts
 */
void processor_interrupts_init(void);

#endif
