#ifndef MICRONIX_SYSCALL_H
#define MICRONIX_SYSCALL_H

#define SYSCALL_TEST 0

#define NUM_SYSCALLS 1

#ifdef __KERNEL__
struct process_context;

typedef void (*syscall_fn)( struct process_context* );

/* Array of all syscalls */
extern const syscall_fn syscalls[];

#endif /* __KERNEL__ */

#endif
