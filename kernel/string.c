#include <micronix/string.h>
#include <micronix/uart.h>

int kstrlen(const char* string){
    int len = 0;

    while( string[ len ] != '\0' ) len++;

    return len;
}

void* kmemset(void* ptr, int value, uint32_t num){
    uint32_t x;
    uint8_t* data = ptr;

    for( x = 0; x < num; x++ ){
        data[ x ] = value;
    }

    return ptr;
}

void _printk(const char* format, ... ){
}
