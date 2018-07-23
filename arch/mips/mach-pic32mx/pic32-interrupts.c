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
#define IFS0 PIC32_R(0x81030)
#define IEC0 PIC32_R(0x81060)
#define IPC0 PIC32_R(0x81090)

/* Set by linker script */
extern int exception_base_address;
extern int vector_size;

static void increment_cp0_compare(void){
    uint32_t cp0_tmp = mips_read_c0_register(CP0_COUNT, 0);

    cp0_tmp += 80000000;

    mips_write_c0_register(CP0_COMPARE,0, cp0_tmp);
}

void interrupts_init(){
    unsigned int cp0_tmp;

    asm volatile("di");

    cp0_tmp = mips_read_c0_register(CP0_STATUS, 0);
    cp0_tmp |= CP0_STATUS_BEV;
    mips_write_c0_register(CP0_STATUS, 0, cp0_tmp);

    /* Set EBase(controlled by linker script) */
    mips_write_c0_register(CP0_EBASE, CP0_EBASE_SELECT, exception_base_address);
    /* Set vector spacing(controlled by linker script*/
    mips_write_c0_register(CP0_INTCTL, CP0_INTCTL_SELECT, vector_size << 5);

    cp0_tmp = mips_read_c0_register(CP0_CAUSE, 0);
    cp0_tmp |= CP0_CAUSE_IV;
    mips_write_c0_register(CP0_CAUSE, 0, cp0_tmp);

    cp0_tmp = mips_read_c0_register(CP0_STATUS, 0);
    cp0_tmp &= ~(CP0_STATUS_BEV | CP0_STATUS_EXL);
    //cp0_tmp &= ~(CP0_STATUS_BEV | CP0_STATUS_EXL | CP0_STATUS_ERL);
    mips_write_c0_register(CP0_STATUS, 0, cp0_tmp);

    /* Interrupt control - enable multi-vector interrupts */
    INTCON = (0x01 << 12);
    asm volatile("ei");

cp0_tmp = mips_read_c0_register(CP0_STATUS,0);
console_write("CP0_STATUS=0x");
console_printhex(cp0_tmp);
console_write("\r\n");

//return;
//-----------CT
    increment_cp0_compare();
  /* Clear the interrupt */
  IFS0 |= (0x01);
    /* Set core timer interrupt priority */
    IPC0 |= (7 << 2);
    /* Enable core timer interrupt */
    IEC0 |= (0x01);
console_write("INIT CT INTR\r\n");
console_write("IEC0=0x");
console_printhex(IEC0);
console_write("\r\n");
console_write("IPC0=0x");
console_printhex(IPC0);
console_write("\r\n");
{
  uint32_t compare = mips_read_c0_register(CP0_COMPARE,0);
  uint32_t count = mips_read_c0_register(CP0_COUNT, 0);
  console_write("compare = 0x");
  console_printhex(compare);
  console_write("\r\ncount=0x");
  console_printhex(count);
  console_write("\r\n");
  if( count > compare ){
    console_write("ERR: count > compare ??\r\n");
  }
}
//-----------END CT

}

int coretimer_int(int cause, int EPC ){
console_write("CT");
  change_led();

  increment_cp0_compare();

  /* Clear the interrupt */
  IFS0 |= (0x01);

  return EPC;
}
