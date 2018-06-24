#ifndef MICRONIX_STACK_H
#define MICRONIX_STACK_H

#include <generated/autoconf.h>
#include <micronix/compiler_types.h>

typedef uint32_t      stack_t[CONFIG_STACK_SIZE];

extern stack_t system_stack;

int stack_alloc( stack_t** );

int stack_free( stack_t* );

void stack_init(void);

#endif
