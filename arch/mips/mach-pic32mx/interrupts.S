# 
# Interrupt handling code for PIC32MX
#

#include <coprocessor-regs.h>

.text

#define ISR(vector) \
  .globl _isr_##vector; \
  .section ._isr_##vector; \
  .type _isr_##vector, @function; \
_isr_##vector: \
  rdpgpr $sp, $sp;  \
  mfc0 $k0, $CP0_CAUSE \

#
# Save the ISR state
#
isr_save:
  nop

#ISR(0)

