#include <micronix/processor_init.h>
#include <pic_config.h>
#include <pic32-clocks.h>
#include <asm/io.h>
#include <coprocessor-regs.h>

static void pic32_ram_init(void){
    /* Copy the .data image from flash to ram.
     * Linker places it at the end of .text segment. */
    extern void _etext(void);
    extern unsigned int __data_start;
    extern unsigned int _edata;
    unsigned *src = (unsigned int*) &_etext;
    unsigned *dest = &__data_start;
    unsigned *limit = &_edata;
    while (dest < limit) {
        /*printf("copy %08x from (%08x) to (%08x)\n", *src, src, dest);*/
        *dest++ = *src++;
    }
}

static void pic32_reset_count_register(void){
    asm volatile("di");
    asm volatile("ehb");
    mips_write_c0_register(CP0_COUNT, 0, 0);
}

void processor_init(){
    pic32_ram_init();
    pic32_reset_count_register();
}

uint32_t pic32_get_sysclk_hz(){
    /* Microchip documentation:
     * SYSCLK = (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
     *
     * FPLLODIV and FPLLMUL can be read from OSCCON,
     * FPLLIDIV must be read from config bits
     */
    uint32_t osccon = readl(OSCCON);
    int pllodiv = (osccon >> 27) & 0x07; /* FPLLODIV config */
    int pllmult = (osccon >> 16) & 0x07; /* FPLLMUL config */
    int pllidiv = DEVCFG1 & DEVCFG2_FPLLIDIV_MASK;
                 /* OSC on Max32 = 8 mHz */
    uint32_t hz = 8000 / pllidiv * pllmult / pllodiv;

    /* TODO this needs to actually calculate the speed
     * if you are on the internal oscillator
     */

    return hz;
}

uint32_t pic32_get_peripheralbus_hz(){
    int divisor;
    int pbdiv = readl( OSCCON );
    pbdiv = pbdiv >> 19;
    pbdiv &= 0x3;

    switch( pbdiv ){
    case 0: divisor = 1; break;
    case 1: divisor = 2; break;
    case 2: divisor = 4; break;
    case 3: divisor = 8; break;
    }

    return pic32_get_sysclk_hz() / divisor;
}
