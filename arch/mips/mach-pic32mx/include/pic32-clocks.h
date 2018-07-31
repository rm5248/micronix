#ifndef PIC32_CLOCKS_H
#define PIC32_CLOCKS_H

#define OSCCON 0xBF80F000

/* Bits for oscillator selection */
#define OSC_INTERNAL_FRC     0
#define OSC_INTERNAL_FRC_PLL 1
#define OSC_POSC             2
#define OSC_POSC_PLL         3
#define OSC_SOSC             4
#define OSC_LPRC             5
#define OSC_FRC_DIV_16       6
#define OSC_FRC_DIV_FRCDIV   7

#endif
