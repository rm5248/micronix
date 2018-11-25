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

int kmemcmp(const void* loc1, const void* loc2, uint32_t len){
    int8_t* loc1_u8 = (int8_t*)loc1;
    int8_t* loc2_u8 = (int8_t*)loc2;
    int8_t diff;

    while( len-- ){
        diff = loc1_u8 - loc2_u8;
        if( diff ) break;
        loc1_u8++;
        loc2_u8++;
    }

    return diff;
}

int kstrcmp(const char* str1, const char* str2){
    char diff = 0;

    while( *str1 != '\0' || *str2 != '\0' ){
        diff = *str1 - *str2;
        if( diff ) break;
        str1++;
        str2++;
    }

    return diff;
}
