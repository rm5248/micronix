#include <micro-os/kern_init.h>
#include <micro-os/init.h>
#include <micro-os/uart.h>

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
