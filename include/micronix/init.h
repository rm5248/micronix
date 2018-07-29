#ifndef MICRONIX_INIT_H
#define MICRONIX_INIT_H

typedef int (*initcall_t)(void);
typedef int (*exitcall_t)(void);

/**
 * This function is to initialize ONLY the board console
 * (if available).  Once the board console has been initialized
 * then the rest of the kernel will startup, followed by
 * the normal board init
 */
//void board_console_init(void);

/**
 * Initialize the board.  Internal kernel data structures have been
 * initalized by this point
 */
//void board_init(void);

#endif
