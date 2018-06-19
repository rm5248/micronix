#ifndef MICRONIX_UART_H
#define MICRONIX_UART_H

/*
struct uart_ops {
    unsigned int (*tx_empty)(struct uart_port *);
    un
}
*/

struct console {
    char    name[16];
    void    (*write)(struct console *, const char *, unsigned);
    void*   data;
};

void console_set(struct console*);
void console_write(const char* data);

//void uart_add_driver();

#endif
