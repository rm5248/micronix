#ifndef MICRONIX_BOARD_H
#define MICRONIX_BOARD_H

/* 
 * This file contains prototypes for the 
 * board initialization functions
 */

/*
 * Initializse the early console for the board.
 * This is generally useful for kernel level debugging.
 */
void board_earlyconsole_init(void) __attribute__((weak));

/*
 * General initialization function for the board.
 * In here, you would do things like initialize the 
 * drivers for the peripherals that you are using.
 */
void board_init(void);

#endif
