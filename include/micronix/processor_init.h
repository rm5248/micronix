#ifndef MICRONIX_PROCESSOR_INIT_H
#define MICRONIX_PROCESSOR_INIT_H

/*
 * Contains function prototypes for processor
 * initialization
 */

/*
 * Called early in the boot process to initialize any clocks
 */
void processor_clocks_init(void);

/*
 * Initializes RAM once clocks have been setup
 */
void processor_ram_init(void);

/*
 * Initialize the interrupt controller on the processor,
 * but don't enable interrupts
 */
void processor_interrupts_init(void);

#endif
