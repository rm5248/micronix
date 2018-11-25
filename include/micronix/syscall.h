#ifndef MICRONIX_SYSCALL_H
#define MICRONIX_SYSCALL_H

#include <stdint.h>
#include <stddef.h>

#define SYSCALL_TEST 0
#define SYSCALL_FORK 1
#define SYSCALL_GETPID 2
#define SYSCALL_OPEN 3
#define SYSCALL_WRITE 4

#define NUM_SYSCALLS 5

long systemcall0(int);
long systemcall1(int,uint32_t*);
long systemcall2(int,uint32_t*,uint32_t*);
long systemcall3(int,uint32_t*,uint32_t*,uint32_t*);

static inline long test(void){ return systemcall0( SYSCALL_TEST ); }
static inline long fork(void){ return systemcall0( SYSCALL_FORK ); }
static inline long getpid(void){ return systemcall0( SYSCALL_GETPID ); }
static inline long open(const char* path, int oflag, ...){ return systemcall2( SYSCALL_OPEN, (uint32_t*)path, &oflag ); }
static inline long write(int fd, const void* buffer, size_t nbyte){ return systemcall3( SYSCALL_WRITE, &fd, (uint32_t*)buffer, (uint32_t*)&nbyte ); }

#ifdef __KERNEL__
struct process_context;

typedef void (*syscall_fn)( struct process_context* );

/* Array of all syscalls */
extern const syscall_fn syscalls[];

#endif /* __KERNEL__ */

#endif
