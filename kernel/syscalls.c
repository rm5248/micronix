#include <micronix/syscalls.h>
#include <micronix/uart.h>

long sys_fork(){
console_write( "in fork\n" );
asm("syscall");
}

long sys_usleep(){

}
