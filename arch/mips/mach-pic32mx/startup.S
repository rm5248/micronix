# PIC32MX startup bootstrap
# Based off of RetroBSD and Microchip sources

.set    noreorder
.set    mips32r2
.set    nomips16
.extern main
.extern u_end

.data
panic_restore_context: .asciiz "Can't restore context"

#
# Reset vector: The main entry point
#
	.section .startup,"ax",@progbits
	.org 0
	.set noreorder
	.ent _reset
	.globl _reset
_reset:
	la $sp,u_end - 16 # start of RAM(note:u_end configured via linker script)
	la $a0,kern_init       # Get the adress of the kern_init method
	jalr $a0
	lui $gp,0x8000 # ????

    # All data structures have now been initialized,
    # and the kernel should be ready to go.
    # Pretend that we are returning from an interrupt.
    j restore_context
    nop

    # If we get here something has gone horribly wrong
    la $v0, panic                  # Get the address of the panic function
    la $a0, panic_restore_context  # String to call panic with
    j panic                        # PANIC



##########################RETROBSD
/*
               .section .exception,"ax",@progbits
_exception_base_: .globl _exception_base_

                .org    0
                .type   _entry_vector_, @function
_entry_vector_: .globl  _entry_vector_
                la      $k0, _reset
                jr      $k0
                nop

*/
/*
 * Data for bootloader.
 */
/*
                .org    0xf8
                .type   _ebase, @object
_ebase:         .word   0x9d000000                      # EBase value

                .type   _imgptr, @object
_imgptr:        .word   -1                              # Image header pointer


#---------------------------------------
# Exception vector: handle exceptions
#
                .org    0x180
                .type   _exception_vector_, @function
_exception_vector_: .globl _exception_vector_

                b       _interrupt_vector_
                nop

                .org    0x200
                .type   _interrupt_vector_, @function
_interrupt_vector_: .globl _interrupt_vector_
                jal     exception
                nop
*/
.end
