#ifndef PIC32_SERIAL_H
#define PIC32_SERIAL_H

#include <micronix/compiler_types.h>

#define UART1_BASE_ADDRESS 0xBF806000
#define UART2_BASE_ADDRESS 0xBF806800
#define UART3_BASE_ADDRESS 0xBF806400
#define UART4_BASE_ADDRESS 0xBF806200
#define UART5_BASE_ADDRESS 0xBF806A00
#define UART6_BASE_ADDRESS 0xBF806600

struct console;

struct pic32_uart_data{
    uint32_t base_address;
    
};

void pic32_init_serial(struct pic32_uart_data* data);
void pic32_console_write(struct console *, const char * text, unsigned len);

#endif
