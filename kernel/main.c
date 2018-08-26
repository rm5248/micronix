#include <micronix/main.h>
#include <pic32-regs.h>

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
