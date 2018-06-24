#include <micronix/kern_init.h>
#include <micronix/init.h>
#include <micronix/uart.h>
#include <micronix/klist.h>
#include <micronix/panic.h>
#include <micronix/process.h>
#include <micronix/stack.h>

void main(void);

void kern_init(){
    board_console_init();

    console_write( "Micronix 0.0.1\r\n" );

    /* Other kernel initialization */
    klist_init();
    process_init();
    stack_init();

    /* Now that our internal data structures 
     * have been setup, call the general board 
     * initialization routine 
     */
    board_init();
console_write( "Done all init!\n" );
main();
}
