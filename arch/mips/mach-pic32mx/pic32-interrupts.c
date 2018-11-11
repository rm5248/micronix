#include <coprocessor-regs.h>
#include <micronix/interrupts.h>
#include <micronix/uart.h>
#include <micronix/processor_init.h>
#include <asm/io.h>
#include <pic32-regs.h>
#include <mach-context.h>
#include <micronix/schedule.h>
#include <micronix/panic.h>
#include <micronix/syscall.h>
#include <micronix/process.h>
#include <micronix/printk.h>
#include <stdint.h>

void change_led(void);

/*
#define PIC32_R(a)              *(volatile unsigned*)(0xBF800000 + (a))
#define INTCON PIC32_R(0x81000)
#define INTCONCLR PIC32_R(0x81004)
#define INTCONSET PIC32_R(0x81008)
//#define IFS0 PIC32_R(0x81030)
#define IFS0CLR PIC32_R(0x81034)
#define IEC0 PIC32_R(0x81060)
#define IEC0SET PIC32_R(0x81068)
#define IPC0 PIC32_R(0x81090)
#define IPC6 PIC32_R(0x810F0)

*/
//#define IPTMR           PIC32_R (0x81020)       /* Temporal Proximity Timer */

int coretimer_int(int cause, int EPC );
//void _isr_0(void);

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

    writel(INTCON, 0);
}

static void enable_coretimer(void){
//increment_cp0_compare();
//writel(IFS0,0);
//IFS0 = 0;
//IPC0 = (0x07 << 2);
//IEC0 = 0x01;
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

void processor_interrupts_init(){
    unsigned int cp0_tmp;
    int vector_size = 32;
    extern void _exception_base_(void);

//memory_init();
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
     * BEV = 1(note: this is what the datasheet says,
     *         but in reality it seems that it should
     *         actually be 0)
     */

    mips_write_c0_register(CP0_STATUS, 0, 0);
    asm volatile("ehb");

    /* Interrupt control - enable single-vector interrupts */
    //INTCON = 0;
    writel(0, INTCON);
}

void main(void);

int coretimer_int(int cause, int EPC ){
//console_write("CT");
  change_led();
main();

  //increment_cp0_compare();

  /* Clear the interrupt */
  //IFS0CLR = 0x01;

  return EPC;
}

static void handle_irq(void){
    /*
     * We need to convert the vector number into an irq number
     * before we can pass it on to the kernel to handle
     */
    int irq_number = 0;
    uint32_t ifs;
    uint32_t bit_pos;

    pr_debug( "Got interrupt\r\n");

    ifs = readl(IFS0);
    for( bit_pos = 0; bit_pos < 32; bit_pos++ ){
        if( ifs & (0x01 << bit_pos) ){
            /* There is an active interrupt here */
            goto kernel_handle;
        }
        irq_number++;
    }

    ifs = readl(IFS1);
    for( bit_pos = 0; bit_pos < 32; bit_pos++ ){
        if( ifs & (0x01 << bit_pos) ){
            /* There is an active interrupt here */
            goto kernel_handle;
        }
        irq_number++;
    }

    ifs = readl(IFS2);
    for( bit_pos = 0; bit_pos < 12; bit_pos++ ){
        if( ifs & (0x01 << bit_pos) ){
            /* There is an active interrupt here */
            goto kernel_handle;
        }
        irq_number++;
    }

kernel_handle:
    interrupt_handle(irq_number);
}

static void handle_syscall( struct process_context* context ){
    int32_t syscall_number = PROCESS_CONTEXT_SYSCALL_NUMBER( context );
    syscall_fn syscall;

    if( syscall_number < 0 || syscall_number > NUM_SYSCALLS ){
        /* bad syscall: force sys_exit */
        pr_warn( "bad syscall number %d: forcing exit\n", syscall_number );
    }

    syscall = syscalls[ syscall_number ];

    syscall( context );
}

/*
 * Called from the exception and interrupt vector
 *
 * Returns the context to restore to
 */
struct process_context* exception( const struct process_context* context ){
    uint32_t cause;
    struct process_context* current_context;

    cause = mips_read_c0_register( CP0_CAUSE, 0 );

    pr_debug( "Exception: cause = 0x%08X, excode = 0x%X\r\n",
        cause,
        (cause & CP0_CAUSE_MASK) >> 2 );

    /*
     * First update the context for our current process, so that we can
     * modifiy it appropriately(e.g. by a syscall)
     */
    scheduler_update_current_context(context);
    current_context = scheduler_current_process()->context;

    /* need to check cause register first, see waht kind of error this is.
     * if interrupt, call interrupt_handle
     * if address/bus/reserved instruction error, signal the current process
     * if syscall, call correct syscall(syscall_handle?)
     */

    switch( cause & CP0_CAUSE_MASK ){
    case CP0_CAUSE_EXCODE_INT: 
        handle_irq();
        break;
    case CP0_CAUSE_EXCODE_SYS:
        handle_syscall( current_context );
        break;
    default:
        panic( "No handling for this exception\n" );
    }


    /*
     * The current process may have been changed,
     * so grab it to be safe.
     */
    current_context = scheduler_current_process()->context;

    return current_context;
}
