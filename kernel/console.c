#include <micronix/uart.h>
#include <micronix/string.h>

static struct console *primary_console = NULL;

void console_set(struct console *console){
    primary_console = console;
}

void console_write(const char* data){
    if( primary_console ){
        primary_console->write(primary_console, data, kstrlen(data) );
    }
}

static char * itoa( int value, char * str, int base )
{
    char * ptr;
    char * low;
    char * rc;
    // Check for supported base.
    if ( base < 2 || base > 36 )
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Set '-' for negative decimals.
    if ( value < 0 && base == 10 )
    {
        *ptr++ = '-';
    }
    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

void console_printint(int value){
    char data[ 10 ];
    if( !primary_console ){
        return;
    }

    itoa(value, data, 10 );
    primary_console->write(primary_console, data, kstrlen(data) );
}

void console_printhex(int value){
    char data[ 10 ];
    if( !primary_console ){
        return;
    }

    itoa(value, data, 16 );
    primary_console->write(primary_console, data, kstrlen(data) );
}
