#include <micronix/processor_init.h>
#include <pic_config.h>
#include <asm/io.h>

#define OSCCON 0xBF80F000

void processor_clocks_init(){
  /* No need to configure anything, set by configuration bits */
}

void processor_ram_init(){
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

uint32_t pic32_get_sysclk_mhz(){
    return 80000000;
}

uint32_t pic32_get_peripheralbus_mhz(){
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

    return pic32_get_sysclk_mhz() / divisor;
}
