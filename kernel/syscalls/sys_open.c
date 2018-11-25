#include <generated/autoconf.h>
#include <micronix/process.h>
#include <micronix/schedule.h>
#include <mach-context.h>
#include <micronix/fsbuiltin.h>
#include <micronix/errno.h>
#include <micronix/string.h>
#include <micronix/printk.h>
#include <stddef.h>

void sys_open( struct process_context* context ){
    struct pcb* pcb = scheduler_current_process();
    struct fs_entry* entry;
    int ret;
    int fd_idx;
    int fs_idx = 0;
    int found = 0;

    /* First let's see if we have an available FD */
    for( fd_idx = 0; fd_idx < CONFIG_MAX_PROCESS_FDS; fd_idx++ ){
        if( pcb->fds[fd_idx] == 0 ){
            break;
        }
    }

    /* There is no available FD */
    if( fd_idx == CONFIG_MAX_PROCESS_FDS ){
        ret = -ENFILE;
        goto out;
    }

    /* Find the file(if it exists) */
    do{
        entry = &(filesystem[ fs_idx ]);
        if( entry->name == NULL ) break;
        if( kstrcmp( entry->name, (const char*)PROCESS_CONTEXT_ARG(context,0) ) == 0 ){
            found = 1;
            break;
        }
        fs_idx++;
    }while( 1 );
    
    if( !found ){
        ret = -ENOENT;
        goto out;
    }

    /* The file was found */
    pcb->fds[fd_idx] = &filesystem[fs_idx];
    ret = fd_idx;

out:
    PROCESS_CONTEXT_RETVAL(ret, context);
}
