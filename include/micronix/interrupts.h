#ifndef MICRONIX_INTERRUPTS_H
#define MICRONIX_INTERRUPTS_H

#define IRQ_NOT_HANDLED 0
#define IRQ_HANDLED 1

typedef int irqreturn_t;

typedef irqreturn_t (*irq_handler_t)(int irq_number, void* dev_id);

/* Initialize the interrupt controller */
void interrupts_init(void);

/* 
 * Handle the given interrupt given its number
 */
void interrupt_handle(int irq_number);

void interrupt_set_handler(int irq_number, 
                           irq_handler_t handler, 
                           unsigned long irqflags, 
                           const char* devname, 
                           void* dev_id);

#endif
