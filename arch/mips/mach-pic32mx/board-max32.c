#include "pic_config.h"

#include <micronix/pic32-serial.h>
#include <pic32-coretimer.h>
#include <pic32-regs.h>
#include <micronix/uart.h>
#include <micronix/console.h>
#include <micronix/printk.h>
#include <micronix/board.h>
#include <micronix/process.h>
#include <micronix/syscall.h>
#include <pic32-coretimer.h>

PIC32_DEVCFG (
DEVCFG0_DEBUG_DISABLED,     /* ICE debugger enabled */

DEVCFG1_FNOSC_PRIPLL |   /* Primary osciallator w/ PLL */
DEVCFG1_POSCMOD_HS |   /* HS oscillator */
//DEVCFG1_FSOSCEN |      /* Enable secondary oscillator */
//DEVCFG1_OSCIOFNC |          /* CLKO output active */
DEVCFG1_FPBDIV_2 |          /* Peripheral bus clock = SYSCLK/2 */
DEVCFG1_FCKM_DISABLE |      /* Fail-safe clock monitor disable */
DEVCFG1_WDTPS_1048576 |         /* Watchdog postscale = 1/1048576 */
DEVCFG1_IESO,               /* Oscillator switch-over */

DEVCFG2_FPLLIDIV_2 |        /* PLL divider = 1/2 */
DEVCFG2_FPLLMUL_20 |        /* PLL multiplier = 20x */
DEVCFG2_UPLLIDIV_12 |        /* USB PLL divider = 1/2 */
DEVCFG2_UPLLDIS |           /* Disable USB PLL */
DEVCFG2_FPLLODIV_1,         /* PLL postscaler = 1/1 */

DEVCFG3_USERID(0xffff) |    /* User-defined ID */
DEVCFG3_FSRSSEL_7 |         /* Assign irq priority 7 to shadow set */
DEVCFG3_FETHIO);            /* Default Ethernet i/o pins */

static struct pic32_uart_data uart1 = {
    .base_address = UART1_BASE_ADDRESS
};

static struct console max32_console = {
    .name = "console",
    .write = pic32_console_write,
    .data = &uart1
};

static int process_change_a3(void){
    int on = 0;
    int counter = 0;

    TRISA = ~(0x01 << 3);
    PORTA = 0;

    while( 1 ){
        if( on ){
            LATA = (0x01 << 3);
        }else{
            LATA = ~(0x01 << 3);
        }

            counter++;
            if( counter % 100000 == 0 ){
                on = !on;
            }
        //sys_usleep( 1000 * 250 );
    }

    return 0;
}

static int process_change_c1(void){
    int on = 0;
    int counter = 0;

    TRISC = 0x01;
    PORTC = 0;
//    PORTCCLR = 0x01;

    while( 1 ){
        if( on ){
            LATC = 1;
        }else{
            LATC = ~1;
        }

        counter++;
        if( counter % 100000 == 0 ){
            on = !on;
        }

    }

    return 0;
}

/* CHIPKIT has RC1 and RA3 as LEDs */
static int max32_init_process(void){
    /* This is a (very simple) vesion of /sbin/init */
    int forkval;

    forkval = fork();
    switch( forkval ){
    case 0: 
        printk( "child process, pid %d\r\n", getpid() );
        process_change_c1();
        break;
    case -1:
        printk( "fork failed\r\n" );
        break;
    default:
        printk( "parent process\r\n" );
    }

    process_change_a3();

    return 0;
}

void board_earlyconsole_init(){
    pic32_init_serial( &uart1 );
    console_set( &max32_console );
}

void board_init(){
    struct pic32_coretimer timer_data = {
        .interrupt_ticks = 2000000,
    };

    pic32_coretimer_init(&timer_data);

    process_create_first( max32_init_process );
}

