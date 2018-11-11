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

void* kmemcpy(void* dest, const void* src, uint32_t len){
    uint8_t* dest_data = dest;
    const uint8_t* src_data = src;

    /* TODO this will be much faster if we can do aligned memory access */

    while( len-- ){
        *dest_data++ = *src_data++;
    }

    return dest;
}
