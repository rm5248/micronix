#include <micronix/stack.h>
#include <micronix/klist.h>
#include <micronix/panic.h>
#include <micronix/errno.h>
#include <micronix/string.h>

static stack_t stacks[ CONFIG_MAX_STATIC_PROCESSES ];
static struct KList available_stacks;

stack_t system_stack;

int stack_alloc( stack_t** stack ){
    return klist_pop_front( &available_stacks, (void**)stack );
}

int stack_free( stack_t* stack ){
    union KListKey key;

    if( stack == NULL ){
        return -EINVAL;
    }

    key.ui = 0;
    kmemset( stack, 0, sizeof( stack_t ) );
    return klist_append( &available_stacks, key, stack );
}

void stack_init(){
   int x;

   klist_reset( &available_stacks, NULL, NULL );

   for( x = 0; x < CONFIG_MAX_STATIC_PROCESSES; x++ ){
       if( stack_free( &stacks[ x ] ) < 0 ){
           panic( "bad stack" );
       }
   } 
}

