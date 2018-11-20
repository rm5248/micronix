#ifndef PIC32_CORETIMER_H
#define PIC32_CORETIMER_H

#include <stdint.h>

struct pic32_coretimer{
    int32_t interrupt_ticks;
};

void pic32_coretimer_init(const struct pic32_coretimer* data);

#endif
