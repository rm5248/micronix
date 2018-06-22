#include <micronix/uart.h>
#include <micronix/string.h>

static struct console *primary_console;

void console_set(struct console *console){
    primary_console = console;
}

void console_write(const char* data){
    if( primary_console ){
        primary_console->write(primary_console, data, kstrlen(data) );
    }
}
