#ifndef MICRONIX_STRING_H
#define MICRONIX_STRING_H

#include <stdint.h>

/**
 * Get the length of a string
 */
int kstrlen(const char* string);

/**
 * Set a block of memory
 */
void* kmemset(void* ptr, int value, uint32_t num);

/**
 * Copy a block of memory
 */
void* kmemcpy(void* dest, const void* src, uint32_t len);

#endif
