#ifndef MICRONIX_MODULE_H
#define MICRONIX_MODULE_H

#include <micronix/init.h>

#define MODULE_INIT(fn) static initcall_t __initcall_##fn \
       __attribute__((__section__(".module.init"))) = fn;

#define INITCALL __section(".module.init")

#endif
