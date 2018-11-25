#ifndef MICRONIX_CHARDEV_H
#define MICRONIX_CHARDEV_H

#define MAKE_MAJOR_MINOR(major,minor) ((minor << 8) | major)
#define MAJOR_FROM_MAJMIN(majmin) ((majmin >> 8) & 0xFF)
#define MINOR_FROM_MAJMIN(majmin) (majmin & 0xFF)

/**
 * Chardev - a character device
 */
struct chardev{
    int (*open)(void* driver_data);
    int (*write)(void* driver_data);
    void *driver_data;
    /* Major/minor device number */
    int16_t majmin;
};

/**
 * Must be defined in board support file
 */
extern struct chardev character_devices[];

#define CHARDEV_END {0}

#endif
