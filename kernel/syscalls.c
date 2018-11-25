#include <micronix/syscall.h>
#include <micronix/uart.h>

struct process_context;

void sys_test( struct process_context* );
void sys_fork( struct process_context* );
void sys_getpid( struct process_context* );
void sys_open( struct process_context* );
void sys_write( struct process_context* );

const syscall_fn syscalls[] = {
    sys_test, /* 0 = test */
    sys_fork,
    sys_getpid,
    sys_open,
    sys_write,
};
