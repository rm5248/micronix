#include <micronix/module.h>
#include <micronix/printk.h>
#include <stddef.h>

extern struct module_info __module_info_begin[];
extern struct module_info __module_info_end;

void modules_init(void){
    int x;

    for( x = 0; x < 128; x++ ){
        if( &__module_info_begin[x] == &__module_info_end ) break;
        pr_debug( "Initializing module %s\r\n", __module_info_begin[x].module_name );

        __module_info_begin[x].init();
    }
}
