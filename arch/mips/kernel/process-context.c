#include <stdint.h>
#include <mach-context.h>
#include <generated/autoconf.h>
#include <micronix/errno.h>
#include <micronix/string.h>
#include <micronix/klist.h>
#include <micronix/process.h>
#include <micronix/printk.h>
#include <stddef.h>

#ifdef CONFIG_STATIC_PROCESS_LIST
static struct process_context all_context[ CONFIG_MAX_STATIC_PROCESSES ];
#endif
static struct KList context_avail;

void process_context_init(){
    int x;
    union KListKey key;

    klist_reset( &context_avail, NULL, NULL );

#ifdef CONFIG_STATIC_PROCESS_LIST
    key.ui = 0;
    kmemset( all_context, 0, sizeof(all_context) );
    for( x = 0; x < CONFIG_MAX_STATIC_PROCESSES; x++ ){
        klist_append( &context_avail, key, &all_context[ x ] );
    }
#endif
}

void process_context_set_pc( struct process_context* context, int pc ){
    context->pc = pc;
}

int process_context_allocate(struct process_context** context){
    int retval;

    if( context == NULL ){
        retval = -EINVAL;
        goto out;
    }

    retval = klist_pop_front( &context_avail, (void**)context );

out:
    return retval;
}

int process_context_free(struct process_context* context){
    int retval;
    union KListKey key;

    if( context == NULL ){
        retval = -EINVAL;
        goto out;
    }

    key.ui = 0;
    kmemset(context, 0, sizeof(struct process_context) );
    retval = klist_append( &context_avail, key, context);

out:
    return retval;
}

int process_context_set_stack(struct process_context* context, stack_t* stack){
    /* Stack grows downwards, so need to get the END of the stack */
    context->sp = (int)stack + sizeof(stack_t);
    context->fp = (int)stack + sizeof(stack_t);

    return 0;
}

int process_context_fix_stack(const struct pcb* original, struct pcb* newproc){
    int32_t stackdiff;

    stackdiff = (void*)original->stack - (void*)newproc->stack;

    newproc->context->sp += stackdiff;
    newproc->context->fp += stackdiff;

    return 0;
}

int process_context_increment_pc_after_syscall(struct process_context* context){
    context->pc += 4;

    return 0;
}
