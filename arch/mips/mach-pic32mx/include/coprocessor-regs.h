#ifndef COPROCESSOR_REGS_H
#define COPROCESSOR_REGS_H

#define CP0_HWREna   7  /* Enables access via RDHWR instruction to selected registers in non-priviliged mode */
#define CP0_BADVADDR 8  /* Address of most recent address-related exception */
#define CP0_COUNT    9  /* Processor cycle count */
#define CP0_COMPARE  11 /* Core timer interrupt control */
#define CP0_STATUS   12 /* Processor status and control */
#define CP0_INTCTL   12 /* Interrupt control register */
#define CP0_INTCTL_SELECT 1
#define CP0_SRSCTL_SELECT 2
#define CP0_SRSMAP_SELECT 3
#define CP0_CAUSE    13 /* Cause of the last exception */
#define CP0_EPC      14 /* Program counter at last exception */
#define CP0_PRID     15 /* Processor identification and revision */
#define CP0_EBASE    15 /* Exception base of exception vectors */
#define CP0_EBASE_SELECT 1
#define CP0_CONFIG   16

#define CP0_STATUS_BEV (0x01 << 22) /* Bootstrap exception vector control bit */
#define CP0_STATUS_EXL (0x01 << 1) /* Exception level bit */
#define CP0_STATUS_ERL (0x01 << 2) /* Error level bit */
#define CP0_STATUS_CU0 (0x01 << 28) /* Allow access to coprocessor 0 from userspace */
#define CP0_CAUSE_IV (0x01 << 23) /* Interrupt vector bit */

/*
 * Read C0 coprocessor register.
 */
#define mips_read_c0_register(reg,sel) \
    ({  int __value; \
        asm volatile ( \
        "mfc0   %0, $%1, %2" \
        : "=r" (__value) : "K" (reg), "K" (sel)); \
        __value; \
    })

/*
 * Write C0 coprocessor register.
 */
#define mips_write_c0_register(reg, sel, value) \
    do { \
        asm volatile ( \
        "mtc0   %z0, $%1, %2 \n ehb" \
        : : "r" ((unsigned int) (value)), "K" (reg), "K" (sel)); \
    } while (0)

#endif
