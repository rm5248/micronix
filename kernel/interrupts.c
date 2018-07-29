#include <micronix/interrupts.h>
#include <generated/autoconf.h>
#include <micronix/panic.h>
#include <micronix/compiler_types.h>
#include <micronix/uart.h>

struct irq_handling{
    irq_handler_t irqhandle;
    void* dev_id;
};

static struct irq_handling irqhandlers[ CONFIG_MAX_IRQS ];

/* Default IRQ handler */
static irqreturn_t default_handler(int irqnum, void* dev_id){
    return IRQ_NOT_HANDLED;
}

void interrupts_init(){
    int x;

    for( x = 0; x < CONFIG_MAX_IRQS; x++ ){
        irqhandlers[ x ].irqhandle = default_handler;
        irqhandlers[ x ].dev_id = NULL;
    }
}

void interrupt_handle(int irq_number){
    irqreturn_t ret;
    struct irq_handling handle;

    if( irq_number < 0 || 
        irq_number > CONFIG_MAX_IRQS ){
        panic( "bad irq number" );
    }

    handle = irqhandlers[irq_number];
    ret = handle.irqhandle(irq_number, handle.dev_id);
    if( ret == IRQ_NOT_HANDLED ){
        panic( "irq not handled" );
    }
}

void interrupt_set_handler(int irq_number, 
                           irq_handler_t handler, 
                           unsigned long irqflags, 
                           const char* devname, 
                           void* dev_id){
    if( irq_number < 0 ||
        irq_number > CONFIG_MAX_IRQS ){
        return;
    }

    irqhandlers[irq_number].irqhandle = handler;
    irqhandlers[irq_number].dev_id = dev_id;
}
