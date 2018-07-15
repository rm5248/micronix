/*
void __attribute__ ((interrupt)) coretimer_int (void){

}
*/

/*
__attribute__((section("._isr_0")))
__attribute__ ((interrupt,use_shadow_register_set))
void coretimer_int2 (void){
}
*/

/*
 * Read C0 coprocessor register.
 */
#define mips_read_c0_register(reg,sel) \
    do{  int __value; \
        asm volatile ( \
        "mfc0   %0, $%1, %2" \
        : "=r" (__value) : "K" (reg), "K" (sel)); \
        __value; \
    }while(0)

/*
 * Write C0 coprocessor register.
 */
#define mips_write_c0_register(reg, sel, value) \
    do { \
        asm volatile ( \
        "mtc0   %z0, $%1, %2 \n ehb" \
        : : "r" ((unsigned int) (value)), "K" (reg), "K" (sel)); \
    } while (0)


int coretimer_int(int cause, int EPC ){

  return EPC;
}
