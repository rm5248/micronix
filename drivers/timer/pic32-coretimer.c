#include <micronix/coretimer.h>
#include <micronix/interrupts.h>
#include <micronix/string.h>
#include <micronix/schedule.h>
#include <asm/io.h>
#include <micronix/printk.h>

#include <pic32-regs.h>
#include <pic32-irq.h>
#include <coprocessor-regs.h>
#include <pic32-coretimer.h>
#include <stddef.h>

static struct pic32_coretimer driver_data;

static void increment_cp0_compare(void){
    uint32_t cp0_tmp = mips_read_c0_register(CP0_COUNT, 0);

    cp0_tmp += driver_data.interrupt_ticks;

    mips_write_c0_register(CP0_COMPARE,0, cp0_tmp);
}

static irqreturn_t pic32_coretimer_interrupt(int irq_number, void* dev_id){
    /* Clear the pending interrupt */
    writel(0x1, IFS0CLR);
    /* Write the compare register to reset the interrupt */
    increment_cp0_compare();

    /* run a new process */
    scheduler_dispatch();

    return IRQ_HANDLED;
}

void pic32_coretimer_init(const struct pic32_coretimer* data){
    kmemcpy( &driver_data, data, sizeof( struct pic32_coretimer ) );
    interrupt_set_handler(PIC32_IRQ_CORETIMER,
                          pic32_coretimer_interrupt,
                          0,
                          "coretimer",
                          NULL);

    /* Clear any pending interrupt and enable core timer interrupt */
    writel(0x1, IFS0CLR);
    writel(0x07 << 2, IPC0);
    writel(0x1, IEC0SET);

    increment_cp0_compare();
}
