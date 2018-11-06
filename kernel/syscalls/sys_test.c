#include <micronix/panic.h>
#include <micronix/process.h>

void sys_test( struct process_context* context ){
    panic( "sys_test" );
}
