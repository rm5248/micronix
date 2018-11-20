#ifndef MACH_CONTEXT_H
#define MACH_CONTEXT_H

#define PROCESS_CONTEXT_WORDS 33

#ifndef __ASSEMBLER__

#include <micronix/process-context.h>

/*
 * Contains the context of the executing process - 
 * this means all of the registers
 */
struct process_context{
    uint32_t at;
    uint32_t v0;
    uint32_t v1;
    uint32_t a0;
    uint32_t a1;
    uint32_t a2;
    uint32_t a3;
    uint32_t t0;
    uint32_t t1;
    uint32_t t2;
    uint32_t t3;
    uint32_t t4;
    uint32_t t5;
    uint32_t t6;
    uint32_t t7;
    uint32_t s0;
    uint32_t s1;
    uint32_t s2;
    uint32_t s3;
    uint32_t s4;
    uint32_t s5;
    uint32_t s6;
    uint32_t s7;
    uint32_t t8;
    uint32_t t9;
    uint32_t gp;
    uint32_t sp;
    uint32_t fp;
    uint32_t ra;
    uint32_t lo;
    uint32_t hi;
    uint32_t status;
    uint32_t pc;
};

_Static_assert( sizeof( struct process_context ) / 4 == PROCESS_CONTEXT_WORDS, "Process context is not expected size" );

/*
 * Get the argument number from the context.
 */
#define PROCESS_CONTEXT_ARG(number,context) ({\
    int value; \
    if( number == 0 ) value = context->a0;\
    if( number == 1 ) value = context->a1;\
    if( number == 2 ) value = context->a2;\
    if( number == 3 ) value = context->a3;\
    value;\
})

/*
 * Set the return value for the context
 */
#define PROCESS_CONTEXT_RETVAL(value,context) context->v0 = value;

/*
 * Get the syscall number from the process context
 */
#define PROCESS_CONTEXT_SYSCALL_NUMBER(context) context->v0

/*
 * Get the program counter from the context
 */
#define PROCESS_CONTEXT_PC(context) context->pc

#endif /* __ASSEMBLER__ */

#endif
