#include "pic_config.h"

#include <micronix/pic32-serial.h>
#include <pic32-coretimer.h>
#include <pic32-regs.h>
#include <micronix/uart.h>
#include <micronix/board.h>
#include <micronix/process.h>
#include <micronix/syscalls.h>

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

    TRISA = ~(0x01 << 3);
    PORTA = 0;

    while( 1 ){
        if( on ){
            LATA = (0x01 << 3);
        }else{
            LATA = ~(0x01 << 3);
        }

        //sys_usleep( 1000 * 250 );
    }

    return 0;
}

static int process_change_c1(void){
    int on = 0;

    TRISC = ~(0x01 << 0);
    PORTC = 0;

    while( 1 ){
        if( on ){
            LATC = (0x01 << 1);
        }else{
            LATC = ~(0x01 << 1);
        }
    }

    return 0;
}

/* CHIPKIT has RC1 and RA3 as LEDs */
static int max32_init_process(void){
    /* This is a (very simple) vesion of /sbin/init */

/*
    switch( sys_fork() ){
    }
*/

process_change_a3();

    while( 1 ){
    }

    return 0;
}

void board_earlyconsole_init(){
    pic32_init_serial( &uart1 );
    console_set( &max32_console );
}

void board_init(){
    pic32_coretimer_init();

    process_create_first( max32_init_process );
}
