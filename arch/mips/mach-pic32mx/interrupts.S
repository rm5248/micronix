# 
# Interrupt handling code for PIC32MX
#

#include <coprocessor-regs.h>
#include <mach-context.h>

.text

# Note: ISR code taken from output of GCC attribute((__interrupt__))

#define ISR_START(vector) \
  .globl _isr_##vector; \
  .section ._isr,"ax"; \
  .type _isr_##vector, @function; \
_isr_##vector: \
  rdpgpr  $sp,$sp;

#define ISR(vector) \
  .globl _isr_##vector; \
  .section ._isr_##vector; \
  .type _isr_##vector, @function; \
_isr_##vector: \
  rdpgpr  $sp,$sp; \
  mfc0    $k0,$CP0_CAUSE; \
  mfc0    $k1,$CP0_EPC; \
  addiu   $sp,$sp,-16; \
  sw      $k1,12($sp); \
  mfc0    $k1,$12; \
  srl     $k0,$k0,10; \
  sw      $k1,8($sp); \
  ins     $k1,$26,10,6; \
  ins     $k1,$0,1,4; \
  ins     $k1,$0,29,1; \
  mtc0    $k1,$CP0_STATUS; \
  sw      $fp,4($sp); \
  move    $fp,$sp; \
  nop     ; \
  move    $sp,$fp; \
  lw      $fp,4($sp); \
  di      ; \
  ehb; \
  lw      $k1,12($sp); \
  mtc0    $k1,$CP0_EPC; \
  lw      $k1,8($sp); \
  mtc0    $k1,$CP0_STATUS; \
  eret; 

#
#
#
               .section .exception,"ax",@progbits
_exception_base_: .globl _exception_base_

                .org    0x180
                .type   _exception_vector_, @function
  .section ._exception_vector,"ax"; \
_exception_vector_: .globl _exception_vector_

                j       _isr
                nop


# 
# Generic interrupt handler - pass cause and EPC, function returns EPC to resume at
#
  .globl _isr;
  .section ._isr,"ax";
  .type _isr, @function;
  .org 0x200
_isr: 
  move $k0, $sp  # Save the original stack pointer
  addi $sp, -16-PROCESS_CONTEXT_WORDS*4          # Allocate space for registers

  .set noat
  # Save all of our registers
  # ($sp) means treat register data as a memory address
  sw      $at, (16+0*4) ($sp)
  sw      $v0, (16+1*4) ($sp)
  sw      $v1, (16+2*4) ($sp)
  sw      $a0, (16+3*4) ($sp)
  sw      $a1, (16+4*4) ($sp)
  sw      $a2, (16+5*4) ($sp)
  sw      $a3, (16+6*4) ($sp)
  sw      $t0, (16+7*4) ($sp)
  sw      $t1, (16+8*4) ($sp)
  sw      $t2, (16+9*4) ($sp)
  sw      $t3, (16+10*4) ($sp)
  sw      $t4, (16+11*4) ($sp)
  sw      $t5, (16+12*4) ($sp)
  sw      $t6, (16+13*4) ($sp)
  sw      $t7, (16+14*4) ($sp)
  sw      $s0, (16+15*4) ($sp)
  sw      $s1, (16+16*4) ($sp)
  sw      $s2, (16+17*4) ($sp)
  sw      $s3, (16+18*4) ($sp)
  sw      $s4, (16+19*4) ($sp)
  sw      $s5, (16+20*4) ($sp)
  sw      $s6, (16+21*4) ($sp)
  sw      $s7, (16+22*4) ($sp)
  sw      $t8, (16+23*4) ($sp)
  sw      $t9, (16+24*4) ($sp)
  sw      $gp, (16+25*4) ($sp)
  sw      $k0, (16+26*4) ($sp) # original sp is in k0
  sw      $fp, (16+27*4) ($sp)
  sw      $ra, (16+28*4) ($sp)
  .set at

  mfhi    $k0                             # Save special registers
  sw      $k0, (16+29*4) ($sp)

  mflo    $k0
  sw      $k0, (16+30*4) ($sp)

  mfc0    $k0, $CP0_STATUS
  sw      $k0, (16+31*4) ($sp)

  mfc0    $k0, $CP0_EPC
  sw      $k0, (16+32*4) ($sp)

  # Pass a pointer to the process context to the exception handler.
  # The exception handler must not modify this as it is on the
  # stack
  move $a0, $sp
  addi $a0, 16

  jal     exception
  nop

# Restore the context as passed back from our exception handler.
# note that V0 will have this address, so we must store it in
# K0 briefly.
# Note: global function to call from startup.S
.globl restore_context;
.type restore_context, @function;
restore_context:
  move $k0, $v0
  .set noat
  lw      $at, (0*4) ($k0)
  lw      $v0, (1*4) ($k0)
  lw      $v1, (2*4) ($k0)
  lw      $a0, (3*4) ($k0)
  lw      $a1, (4*4) ($k0)
  lw      $a2, (5*4) ($k0)
  lw      $a3, (6*4) ($k0)
  lw      $t0, (7*4) ($k0)
  lw      $t1, (8*4) ($k0)
  lw      $t2, (9*4) ($k0)
  lw      $t3, (10*4) ($k0)
  lw      $t4, (11*4) ($k0)
  lw      $t5, (12*4) ($k0)
  lw      $t6, (13*4) ($k0)
  lw      $t7, (14*4) ($k0)
  lw      $s0, (15*4) ($k0)
  lw      $s1, (16*4) ($k0)
  lw      $s2, (17*4) ($k0)
  lw      $s3, (18*4) ($k0)
  lw      $s4, (19*4) ($k0)
  lw      $s5, (20*4) ($k0)
  lw      $s6, (21*4) ($k0)
  lw      $s7, (22*4) ($k0)
  lw      $t8, (23*4) ($k0)
  lw      $t9, (24*4) ($k0)
  lw      $gp, (25*4) ($k0)
  lw      $sp, (26*4) ($k0)
  lw      $fp, (27*4) ($k0)
  lw      $ra, (28*4) ($k0)
  .set at

  # Restore our status register
#  lw      $k0, (16+31*4) ($k0)
#  mtc0    $k0, $CP0_STATUS

  # restore hi register for overflow
  lw      $k1, (29*4) ($k0)
  mthi    $k1

  # Restore the program counter
  lw      $k1, (32*4) ($k0)
  mtc0    $k1, $CP0_EPC

  # Restore low register for overflow
  lw      $k1, (30*4) ($k0)
  mtlo    $k1

  # Finally, return from our exception
  eret
