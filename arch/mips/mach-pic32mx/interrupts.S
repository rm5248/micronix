# 
# Interrupt handling code for PIC32MX
#

#include <coprocessor-regs.h>

.text

#define ISR(vector) \
  .globl _isr_##vector \
_isr_##vector: \
  rdpgpr $sp, $sp \
  mfc0 k0, CP0_CAUSE

#
# Save the ISR state
#
isr_save:
