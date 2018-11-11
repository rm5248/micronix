#include <micronix/panic.h>
#include <micronix/uart.h>
#include <micronix/printk.h>

void panic( const char* reason ){
    pr_emerg( "**** KERNEL PANIC: %s\r\n", reason );

    lowlevel_panic();
}
