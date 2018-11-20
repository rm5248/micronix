#ifndef MICRONIX_MODULE_H
#define MICRONIX_MODULE_H

#include <micronix/init.h>

#define MODULE_INFO __attribute__((section(".module.info")))

struct module_info{
    void (*init)(void);
    const char* module_name;
};

#endif
