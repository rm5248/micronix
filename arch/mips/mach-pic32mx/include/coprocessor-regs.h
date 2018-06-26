#ifndef COPROCESSOR_REGS_H
#define COPROCESSOR_REGS_H

#define CP0_HWREna   7  /* Enables access via RDHWR instruction to selected registers in non-priviliged mode */
#define CP0_BADVADDR 8  /* Address of most recent address-related exception */
#define CP0_COUNT    9  /* Processor cycle count */
#define CP0_COMPARE  11 /* Core timer interrupt control */
#define CP0_STATUS   12 /* Processor status and control */
#define CP0_CAUSE    13 /* Cause of the last exception */
#define CP0_EPC      14 /* Program counter at last exception */
#define CP0_PRID     15 /* Processor identification and revision */
#define CP0_EBASE    16 /* Exception base of exception vectors */
#define CP0_EBASE_SELECT 1

#endif
