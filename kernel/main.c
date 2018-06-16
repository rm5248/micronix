#include <micro-os/main.h>

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

/* micro-os entry point */
void main(){
	int counter = 0;

	PORTA = 0;

	while( 1 ){
		counter++;
		if( counter % 1000000 == 0 ){
			PORTA = (0x01 << 3);
		}else{
			PORTA = 0;
		}
	}
}
