#ifndef MICRONIX_STRING_H
#define MICRONIX_STRING_H

#include <micronix/compiler_types.h>

/**
 * Get the length of a string
 */
int kstrlen(const char* string);

/**
 * Set a block of memory
 */
void* kmemset(void* ptr, int value, uint32_t num);

/**
 * Print the following message to the console
 */
void _printk(const char* format, ... );

#ifndef CONFIG_DISABLE_PRINTK
#define printk(format,...)
#else
#define printk(format,...) _printk(format, __VA_ARGS__)
#endif

#endif
