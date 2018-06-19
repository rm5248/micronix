#ifndef MICRONIX_PRINTK_H
#define MICRONIX_PRINTK_H

#include <generated/autoconf.h>

#ifdef CONFIG_ENABLE_PRINTK
#define printk(s) __printk(s);
#else
#define printk(s)
#endif

void __printk(const char* message);

#endif
