#include <generated/autoconf.h>
#include <micronix/process.h>
#include <micronix/schedule.h>
#include <micronix/printk.h>
#include <mach-context.h>
#include <micronix/fsbuiltin.h>
#include <micronix/chardev.h>

static int write_chardev(struct fs_entry* entry, const void* data, uint32_t len){
    int major = MAJOR_FROM_MAJMIN(entry->majmin);
    int minor = MAJOR_FROM_MAJMIN(entry->majmin);
    struct chardev* dev = character_devices[major];

    switch(major){
    case MAJOR_TTY:
        break;
    default:
        pr_warn("No handling for chardev with major %d(0x%X)\r\n", major, major);
    }

}

void sys_write( struct process_context* context ){
    struct pcb* pcb = scheduler_current_process();
    int* fd = PROCESS_CONTEXT_ARG(context,0);
    const void* data = PROCESS_CONTEXT_ARG(context,1);
    uint32_t* len = PROCESS_CONTEXT_ARG(context,2);
    struct fs_entry* entry;
    int ret;

    if( *fd < 0 || *fd > CONFIG_MAX_PROCESS_FDS ){
        ret = -EBADF;
        goto out;
    }

    entry = pcb->fds[fd];
    if( entry->permissions & FS_ENTRY_BLOCKDEV ){
    
    }else if( entry->permissions & FS_ENTRY_CHARDEV ){
        ret = write_chardev(entry, data, *len);
    }

out:
    PROCESS_CONTEXT_RETVAL(ret, context);
}
