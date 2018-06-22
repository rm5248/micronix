#include <micronix/kern_init.h>
#include <micronix/init.h>
#include <micronix/uart.h>

void main(void);

void kern_init(){
    board_console_init();

    console_write( "Micronix 0.1.0\r\n" );
    /* Other kernel initialization */


    /* Now that our internal data structures 
     * have been setup, call the general board 
     * initialization routine 
     */
    board_init();
main();
}
