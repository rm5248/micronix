#include <micronix/string.h>

int kstrlen(const char* string){
    int len = 0;

    while( string[ len ] != '\0' ) len++;

    return len;
}
