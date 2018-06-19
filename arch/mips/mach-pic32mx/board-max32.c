#include "pic_config.h"

#include <micro-os/pic32-serial.h>
#include <micro-os/init.h>
#include <micro-os/uart.h>

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
    //.base_address = UART1_BASE_ADDRESS
};

static struct console max32_console = {
    .name = "console",
    .write = pic32_console_write,
    .data = &uart1
};

//TODO calulate thse values by reading DEVCFG, hardcode for now 
//to make sure we get good values
uint32_t pic32_get_sysclk_mhz(){
    return 80000000;
}

uint32_t pic32_get_peripheralbus_mhz(){
    return pic32_get_sysclk_mhz() / 4;
}

void board_console_init(){
    uart1.base_address = UART1_BASE_ADDRESS;
    max32_console.write = pic32_console_write;
    max32_console.data = &uart1;

    pic32_init_serial( &uart1 );
    console_set( &max32_console );
}

void board_init(){
//	jklsadf
}
