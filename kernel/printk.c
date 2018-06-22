#include <micronix/printk.h>
#include <micronix/console.h>
#include <micronix/uart.h>

void __printk(const char* message){
    console_write(message);
}
