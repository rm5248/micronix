void __attribute__ ((interrupt)) coretimer_int (void){

}

__attribute__((section("._isr_0")))
__attribute__ ((interrupt,use_shadow_register_set))
void coretimer_int2 (void){
  volatile int x = 0;
  x += 5;
}
