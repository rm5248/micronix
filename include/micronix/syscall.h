#ifndef MICRONIX_SYSCALL_H
#define MICRONIX_SYSCALL_H

#define SYSCALL_TEST 0
#define SYSCALL_FORK 1
#define SYSCALL_GETPID 2

#define NUM_SYSCALLS 3

long systemcall(int);

static inline long test(void){ return systemcall( SYSCALL_TEST ); }
static inline long fork(void){ return systemcall( SYSCALL_FORK ); }
static inline long getpid(void){ return systemcall( SYSCALL_GETPID ); }

#ifdef __KERNEL__
struct process_context;

typedef void (*syscall_fn)( struct process_context* );

/* Array of all syscalls */
extern const syscall_fn syscalls[];

#endif /* __KERNEL__ */

#endif
