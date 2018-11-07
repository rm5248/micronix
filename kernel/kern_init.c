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
#include <micronix/schedule.h>

void main(void);
void led_init(void);

struct process_context* kern_init(void){
    processor_clocks_init();
    processor_ram_init();

    board_earlyconsole_init();

    console_write( "Micronix 0.0.1\r\n" );

    /* Other kernel initialization */
    klist_init();
    process_init();
    scheduler_init();
    stack_init();
    interrupts_init();
    processor_interrupts_init();
//led_init();

    /* Now that our internal data structures 
     * have been setup, call the general board 
     * initialization routine 
     */
    board_init();

    scheduler_dispatch();
console_write( "Done all init!\n" );

    /*
     * All data structures have been initialized: return the
     * process context to begin execution from
     */
    return scheduler_current_process()->context;
//asm volatile("ei");
//asm volatile("ehb");
//main();
//wait forever
//volatile int a = 5;
//while( a );
}
