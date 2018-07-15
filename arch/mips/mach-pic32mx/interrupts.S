# 
# Interrupt handling code for PIC32MX
#

#include <coprocessor-regs.h>

.text

# Note: ISR code taken from output of GCC attribute((__interrupt__))

#define ISR_START(vector) \
  .globl _isr_##vector; \
  .section ._isr_##vector; \
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
# Save the ISR state
#
isr_save:
  nop


# 
# Core Timer interrupt - pass cause and EPC, function returns EPC to resume at
#
ISR_START(0)
  mfc0    $a0,$CP0_CAUSE; 
  mfc0    $a1,$CP0_EPC; 
  jal     coretimer_int
  nop
  mtc0    $v1,$CP0_EPC
  eret
