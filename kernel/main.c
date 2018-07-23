#include <micronix/main.h>

#define PIC32_R(a)              *(volatile unsigned*)(0xBF800000 + (a))
#define TRISA           PIC32_R (0x86000) /* Port A: mask of inputs */
#define TRISACLR        PIC32_R (0x86004)
#define TRISASET        PIC32_R (0x86008)
#define TRISAINV        PIC32_R (0x8600C)
#define PORTA           PIC32_R (0x86010) /* Port A: read inputs, write outputs */
#define PORTACLR        PIC32_R (0x86014)
#define PORTASET        PIC32_R (0x86018)
#define PORTAINV        PIC32_R (0x8601C)
#define LATA            PIC32_R (0x86020) /* Port A: read/write outputs */
#define LATACLR         PIC32_R (0x86024)
#define LATASET         PIC32_R (0x86028)
#define LATAINV         PIC32_R (0x8602C)
#define ODCA            PIC32_R (0x86030) /* Port A: open drain configuration */
#define ODCACLR         PIC32_R (0x86034)
#define ODCASET         PIC32_R (0x86038)
#define ODCAINV         PIC32_R (0x8603C)

#define TRISC           PIC32_R (0x86080) /* Port C: mask of inputs */
#define TRISCCLR        PIC32_R (0x86084)
#define TRISCSET        PIC32_R (0x86088)
#define TRISCINV        PIC32_R (0x8608C)
#define PORTC           PIC32_R (0x86090) /* Port C: read inputs, write outputs */
#define PORTCCLR        PIC32_R (0x86094)
#define PORTCSET        PIC32_R (0x86098)
#define PORTCINV        PIC32_R (0x8609C)
#define LATC            PIC32_R (0x860A0) /* Port C: read/write outputs */
#define LATCCLR         PIC32_R (0x860A4)
#define LATCSET         PIC32_R (0x860A8)
#define LATCINV         PIC32_R (0x860AC)
#define ODCC            PIC32_R (0x860B0) /* Port C: open drain configuration */
#define ODCCCLR         PIC32_R (0x860B4)
#define ODCCSET         PIC32_R (0x860B8)
#define ODCCINV         PIC32_R (0x860BC)

void main(){
    int counter = 0;
    int on = 0;

    TRISA = ~(0x01 << 3);
    PORTA = 0;

    while( 1 ){
            counter++;
            if( counter % 100000 == 0 ){
                on = !on;
            }
            
            if( on ){
                    LATA = (0x01 << 3);
            }else{
                    LATA = ~(0x01 << 3);
            }
    }
}

void led_init(void){
    TRISC = ~(0x01 << 0);
    PORTC = 0;
}

void change_led(void){
    int on = PORTC & 0x01;

   if( on ){
       LATC = (0x01 << 1);
   }else{
       LATC = ~(0x01 << 1);
   }
}
