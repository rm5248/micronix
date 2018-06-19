#include <micro-os/printk.h>
#include <micro-os/console.h>
#include <micro-os/uart.h>

void __printk(const char* message){
    console_write(message);
}
