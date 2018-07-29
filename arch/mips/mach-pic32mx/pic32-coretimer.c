#include <pic32-coretimer.h>
#include <pic32-irq.h>
#include <pic32-regs.h>
#include <coprocessor-regs.h>
#include <micronix/interrupts.h>
#include <micronix/compiler_types.h>
#include <asm/io.h>
#include <micronix/uart.h>

static void increment_cp0_compare(void){
    uint32_t cp0_tmp = mips_read_c0_register(CP0_COUNT, 0);

    cp0_tmp += 8000000;

    mips_write_c0_register(CP0_COMPARE,0, cp0_tmp);
}

static irqreturn_t coretimer_irq(int irq_number, void* dev_id){
    /* Clear the pending interrupt */
    writel(0x1, IFS0CLR);
    increment_cp0_compare();
    return IRQ_HANDLED;
}

void pic32_coretimer_init(){
    interrupt_set_handler(PIC32_IRQ_CORETIMER,
                          coretimer_irq,
                          0,
                          "coretimer",
                          NULL);

    /* Clear any pending interrupt and enable core timer interrupt */
    writel(0x1, IFS0CLR);
    writel(0x07 << 2, IPC0);
    writel(0x1, IEC0SET);

    increment_cp0_compare();
}
