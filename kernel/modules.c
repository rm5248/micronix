#include <micronix/printk.h>
#include <stddef.h>

typedef void (*module_init_fn)(void);


struct somestruct{
  int a;
  int b;
  int c;
  int d;
  const char* name;
};

extern struct somestruct __module_info_begin[];
extern struct somestruct __module_info_end;

void modules_init(void){
    int x;

printk( "module_info_begin is 0x%08X\r\n", __module_info_begin );
printk( "module_info_end is 0x%08X\r\n", __module_info_end );


    for( x = 0; x < 128; x++ ){
        if( &__module_info_begin[x] == &__module_info_end ) break;
        printk( "example a = %d\r\n", __module_info_begin[x].a);
/*
        printk( "example b = %d\r\n", module_init[x].b);
        printk( "example c = %d\r\n", module_init[x].c);
        printk( "example d = %d\r\n", module_init[x].d);
        printk( "example name = %s\r\n", module_init[x].name);
*/
    }
}
