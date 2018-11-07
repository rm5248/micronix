#include <micronix/compiler_types.h>
#include <mach-context.h>

void process_context_set_pc( struct process_context* context, int pc ){
    context->pc = pc;
}
