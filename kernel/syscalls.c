#include <micronix/syscall.h>
#include <micronix/uart.h>

/*
long sys_fork(){
console_write( "in fork\n" );
asm("syscall");
}

long sys_usleep(){

}
*/

struct process_context;

void sys_test( struct process_context* );

const syscall_fn syscalls[] = {
    sys_test, /* 0 = test */
};
