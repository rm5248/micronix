#include <micronix/panic.h>
#include <micronix/uart.h>

void panic( const char* reason ){
    console_write( "**** KERNEL PANIC: " );
    console_write( reason );
    console_write( "\n" );

    lowlevel_panic();
}
