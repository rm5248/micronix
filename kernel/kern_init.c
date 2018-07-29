#include <micronix/kern_init.h>
#include <micronix/init.h>
#include <micronix/uart.h>
#include <micronix/klist.h>
#include <micronix/panic.h>
#include <micronix/process.h>
#include <micronix/stack.h>
#include <micronix/interrupts.h>
#include <micronix/processor_init.h>
#include <micronix/board.h>

void main(void);
void led_init(void);

void kern_init(){
    processor_clocks_init();
    processor_ram_init();

    board_earlyconsole_init();

    console_write( "Micronix 0.0.1\r\n" );

    /* Other kernel initialization */
    klist_init();
    process_init();
    stack_init();
    interrupts_init();
    processor_interrupts_init();
led_init();

    /* Now that our internal data structures 
     * have been setup, call the general board 
     * initialization routine 
     */
    board_init();
console_write( "Done all init!\n" );
asm volatile("ei");
asm volatile("ehb");
//main();
//wait forever
volatile int a = 5;
while( a );
}
