#ifndef MICRONIX_DEVNUM_H
#define MICRONIX_DEVNUM_H

#include <generated/autoconf.h>

/*
 * Major device numbers used by micronix.
 * Note: these numbers can change, due to the fact that this
 * is an enum that is dynamically created.  The reason for this
 * is to allow for indexing of the major device number into the
 * character_devices array and to not waste space
 */
enum MajorCharDevNum{
    MAJOR_NULL = 0,
#ifdef CONFIG_ENABLE_TTY
    MAJOR_TTY,
#endif
#ifdef CONFIG_ENABLE_I2C
    MAJOR_I2C
#endif
};

#endif
