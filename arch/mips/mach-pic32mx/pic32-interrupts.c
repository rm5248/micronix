#include <coprocessor-regs.h>
#include <micronix/interrupts.h>
#include <micronix/compiler_types.h>
#include <micronix/uart.h>

/*
void __attribute__ ((interrupt)) coretimer_int (void){

}
*/

/*
__attribute__((section("._isr_0")))
__attribute__ ((interrupt,use_shadow_register_set))
void coretimer_int2 (void){
}
*/

/*
 * Read C0 coprocessor register.
 */
#define mips_read_c0_register(reg,sel) \
    ({  int __value; \
        asm volatile ( \
        "mfc0   %0, $%1, %2" \
        : "=r" (__value) : "K" (reg), "K" (sel)); \
        __value; \
    })


/*
 * Write C0 coprocessor register.
 */
#define mips_write_c0_register(reg, sel, value) \
    do { \
        asm volatile ( \
        "mtc0   %z0, $%1, %2 \n ehb" \
        : : "r" ((unsigned int) (value)), "K" (reg), "K" (sel)); \
    } while (0)


void change_led(void);

#define PIC32_R(a)              *(volatile unsigned*)(0xBF800000 + (a))
#define INTCON PIC32_R(0x81000)
#define INTCONCLR PIC32_R(0x81004)
#define INTCONSET PIC32_R(0x81008)
#define IFS0 PIC32_R(0x81030)
#define IFS0CLR PIC32_R(0x81034)
#define IEC0 PIC32_R(0x81060)
#define IEC0SET PIC32_R(0x81068)
#define IPC0 PIC32_R(0x81090)
#define IPC6 PIC32_R(0x810F0)

#define IPTMR           PIC32_R (0x81020)       /* Temporal Proximity Timer */

int coretimer_int(int cause, int EPC );
//void _isr_0(void);

static void increment_cp0_compare(void){
    uint32_t cp0_tmp = mips_read_c0_register(CP0_COUNT, 0);

    cp0_tmp += 8000000;

    mips_write_c0_register(CP0_COMPARE,0, cp0_tmp);
}

static void memory_init(void){
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

#define ST_CU0          0x10000000      /* Access to coprocessor 0 allowed (in user mode) */

static void retrobsd_init(void){
    extern void _etext(void), _exception_base_(void);

    /* Initialize STATUS register: master interrupt disable.
     * Setup interrupt vector base. */
    //mips_write_c0_register(CP0_STATUS, 0, ST_CU0 | CP0_STATUS_BEV);
    mips_write_c0_register(CP0_STATUS, 0, CP0_STATUS_BEV);
    mips_write_c0_register(CP0_EBASE, 1, _exception_base_);
    //mips_write_c0_register(CP0_STATUS, 0, ST_CU0);

    /* Set vector spacing: not used really, but must be nonzero. */
    mips_write_c0_register(CP0_INTCTL, 1, 32);

    /* Clear CAUSE register: use special interrupt vector 0x200. */
    mips_write_c0_register(CP0_CAUSE, 0, CP0_CAUSE_IV);

    /* Config register: enable kseg0 caching. */
//    mips_write_c0_register(CP0_CONFIG, 0,
 //   mips_read_c0_register(CP0_CONFIG, 0) | 3);

    /* Kernel mode, interrupts disabled.  */
    mips_write_c0_register(CP0_STATUS, 0, ST_CU0);
    asm volatile("ehb");

    INTCON = 0;
}

static void enable_coretimer(void){
increment_cp0_compare();
IFS0 = 0;
IPC0 = (0x07 << 2);
IEC0 = 0x01;
asm volatile("nop");
asm volatile("nop");
asm volatile("nop");
    asm volatile("ei");
    asm volatile("ehb");
asm volatile("nop");
asm volatile("nop");
}

/* Set in linker script */
//extern int exception_base_address;

void interrupts_init(){
    unsigned int cp0_tmp;
    int vector_size = 32;
    extern void _exception_base_(void);

memory_init();
//retrobsd_init();

//enable_coretimer();

    asm volatile("di");
    asm volatile("ehb");
    mips_write_c0_register(CP0_COUNT, 0, 0);

    /* Exception vectors are in bootstrap location */
    //cp0_tmp = mips_read_c0_register(CP0_STATUS, 0);
    cp0_tmp = CP0_STATUS_BEV;
    mips_write_c0_register(CP0_STATUS, 0, cp0_tmp);

    /* Set EBase(tells CPU where interrupt handler is) */
    mips_write_c0_register(CP0_EBASE, CP0_EBASE_SELECT, _exception_base_);

    /* Set vector spacing(not used, but can't be 0)*/
    mips_write_c0_register(CP0_INTCTL, CP0_INTCTL_SELECT, vector_size);

    //cp0_tmp = mips_read_c0_register(CP0_CAUSE, 0);
    cp0_tmp = CP0_CAUSE_IV;
    mips_write_c0_register(CP0_CAUSE, 0, cp0_tmp);

    //cp0_tmp = mips_read_c0_register(CP0_STATUS, 0);
    //cp0_tmp |= CP0_STATUS_BEV;
    //mips_write_c0_register(CP0_STATUS, 0, cp0_tmp);

    /*
     * Single vector interrupts mode:
     * EBase != 0
     * IV(Cause<23>) = 1
     * MEVC(INTCON<12>) = 0
     * IE(Status<0)>) = 1
     * BEV = 1
     */

    mips_write_c0_register(CP0_STATUS, 0, ST_CU0);
    asm volatile("ehb");
    /* Interrupt control - enable single-vector interrupts */
    //INTCONCLR = 0x01 << 12;
INTCON = 0;

enable_coretimer();
}

void main(void);

int coretimer_int(int cause, int EPC ){
console_write("CT");
  change_led();
main();

  increment_cp0_compare();

  /* Clear the interrupt */
  IFS0CLR = 0x01;

  return EPC;
}

void exception(void){
    
console_write("EXCEPTION");
main();

}
