#ifndef MICRONIX_FS_BUILTIN_H
#define MICRONIX_FS_BUILTIN_H

#include <stdint.h>
#include <micronix/chardev.h>

#define FS_ENTRY_BLOCKDEV (0x01 << 12)
#define FS_ENTRY_CHARDEV  (0x01 << 13)
#define FS_ENTRY_OTHER_X  (0x01 << 0)
#define FS_ENTRY_OTHER_W  (0x01 << 1)
#define FS_ENTRY_OTHER_R  (0x01 << 2)
#define FS_ENTRY_GROUP_X  (0x01 << 4)
#define FS_ENTRY_GROUP_W  (0x01 << 5)
#define FS_ENTRY_GROUP_R  (0x01 << 6)
#define FS_ENTRY_USER_X   (0x01 << 8)
#define FS_ENTRY_USER_W   (0x01 << 9)
#define FS_ENTRY_USER_R   (0x01 << 10)

#define FS_ENTRY_DEV(namei,permsi,majori,minori) \
{\
    .name = namei,\
    .permissions = permsi,\
    .majmin = MAKE_MAJOR_MINOR(majori,minori),\
}

#define FS_ENTRY(namei,permsi) FS_ENTRY_DEV(namei,permsi,0,0)

#define FS_ENTRY_END { 0 }

struct fs_entry{
    const char* name;
    /*
     * File permissions, and associated information
     *(e.g. block/chardev)
     */
    uint16_t permissions;
    /*
     * Major/minor device number(for drivers)
     * BLOCKDEV or CHARDEV bit must be set in permissions
     */
    uint16_t majmin;
};

extern struct fs_entry filesystem[];

#endif
