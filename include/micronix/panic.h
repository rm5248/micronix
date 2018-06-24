#ifndef MICRONIX_PANIC_H
#define MICRONIX_PANIC_H

/* Print the message and then stop doing anything */
void panic( const char* reason );

/* This should be an assembly function that disables interrupts
 * and runs in a NOP loop
 */
void lowlevel_panic(void);

#endif
