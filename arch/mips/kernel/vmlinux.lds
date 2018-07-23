OUTPUT_FORMAT("elf32-tradlittlemips", "elf32-bigmips",
       "elf32-littlemips")
OUTPUT_ARCH(mips)
ENTRY(_reset)
PROVIDE(exception_base_address = 0x9FC01000);
PROVIDE(vector_size = 0x40);
MEMORY
{
  ram (rw!x): ORIGIN = 0x80000000, LENGTH = 26K
  u0area (rw!x): ORIGIN = 0x80006800, LENGTH = 3K
  uarea (rw!x): ORIGIN = 0x80007400, LENGTH = 3K
  devcfg (r) : ORIGIN = 0x9fc02ff0, LENGTH = 16
  kseg0_program_mem (rx) : ORIGIN = 0x9D000000, LENGTH = 512K
  exception_mem (rx) : ORIGIN = 0x9FC01000, LENGTH = 0x1000
  kseg0_boot_mem (rx) : ORIGIN = 0x9FC00000, LENGTH = 12K-16
  kseg1_boot_mem (rx) : ORIGIN = 0xBFC00000, LENGTH = 0x490
  kseg1_data_mem (w!x) : ORIGIN = 0xA0000000, LENGTH = 0x20000
}
u0 = ORIGIN(u0area);
u = ORIGIN(uarea);
u_end = ORIGIN(uarea) + LENGTH(uarea);
SECTIONS
{
  . = 0x0000;
  .interp : { *(.interp) }
  .hash : { *(.hash) }
  .dynsym : { *(.dynsym) }
  .dynstr : { *(.dynstr) }
  .gnu.version : { *(.gnu.version) }
  .gnu.version_d : { *(.gnu.version_d) }
  .gnu.version_r : { *(.gnu.version_r) }
  .rel.init : { *(.rel.init) }
  .rela.init : { *(.rela.init) }
  .rel.text : { *(.rel.text .rel.text.* .rel.gnu.linkonce.t.*) }
  .rela.text : { *(.rela.text .rela.text.* .rela.gnu.linkonce.t.*) }
  .rel.fini : { *(.rel.fini) }
  .rela.fini : { *(.rela.fini) }
  .rel.rodata : { *(.rel.rodata .rel.rodata.* .rel.gnu.linkonce.r.*) }
  .rela.rodata : { *(.rela.rodata .rela.rodata.* .rela.gnu.linkonce.r.*) }
  .rel.data : { *(.rel.data .rel.data.* .rel.gnu.linkonce.d.*) }
  .rela.data : { *(.rela.data .rela.data.* .rela.gnu.linkonce.d.*) }
  .rel.ctors : { *(.rel.ctors) }
  .rela.ctors : { *(.rela.ctors) }
  .rel.dtors : { *(.rel.dtors) }
  .rela.dtors : { *(.rela.dtors) }
  .rel.got : { *(.rel.got) }
  .rela.got : { *(.rela.got) }
  .rel.sdata : { *(.rel.sdata .rel.sdata.* .rel.gnu.linkonce.s.*) }
  .rela.sdata : { *(.rela.sdata .rela.sdata.* .rela.gnu.linkonce.s.*) }
  .rel.sbss : { *(.rel.sbss .rel.sbss.* .rel.gnu.linkonce.sb.*) }
  .rela.sbss : { *(.rela.sbss .rela.sbss.* .rela.gnu.linkonce.sb.*) }
  .rel.sdata2 : { *(.rel.sdata2 .rel.sdata2.* .rel.gnu.linkonce.s2.*) }
  .rela.sdata2 : { *(.rela.sdata2 .rela.sdata2.* .rela.gnu.linkonce.s2.*) }
  .rel.sbss2 : { *(.rel.sbss2 .rel.sbss2.* .rel.gnu.linkonce.sb2.*) }
  .rela.sbss2 : { *(.rela.sbss2 .rela.sbss2.* .rela.gnu.linkonce.sb2.*) }
  .rel.bss : { *(.rel.bss .rel.bss.* .rel.gnu.linkonce.b.*) }
  .rela.bss : { *(.rela.bss .rela.bss.* .rela.gnu.linkonce.b.*) }
  .rel.plt : { *(.rel.plt) }
  .rela.plt : { *(.rela.plt) }
  .plt : { *(.plt) }
.module.init : { *(.module.init) }
  .boot :
  {
    *(.startup)
  } > kseg0_boot_mem
  .text :
  {
    *(.exception)
    *(.text .stub .text.* .gnu.linkonce.t.*)
    *(.gnu.warning)
    *(.glue_7t) *(.glue_7)
    __rodata_start = . ;
    *(.rodata .rodata.* .gnu.linkonce.r.* .rel.dyn)
    __abiflags = . ;
    *(.MIPS.abiflags)
    *(.dinit)
    . = ALIGN (32 / 8);
    _etext = .;
  } > kseg0_program_mem
  .data : AT (ADDR (.text) + SIZEOF (.text))
  {
    __data_start = . ;
    _gp = .;
    *(.data .data.* .gnu.linkonce.d.*)
    *(.sdata .sdata.* .gnu.linkonce.s.*)
    *(.eh_frame)
    _edata = .;
  } > ram
  .config :
  {
    *(.config3)
    *(.config2)
    *(.config1)
    *(.config0)
  } > devcfg
  .bss ADDR (.data) + SIZEOF (.data) (NOLOAD) :
  {
   __bss_start = .;
   *(.dynbss)
   *(.sbss .sbss.*)
   *(.scommon)
   *(.bss .bss.* .gnu.linkonce.b.*)
   *(COMMON)
   . = ALIGN (32 / 8);
  } > ram
  __bss_end = . ;
  _end = .;
  .stab 0 : { *(.stab) }
  .stabstr 0 : { *(.stabstr) }
  .stab.excl 0 : { *(.stab.excl) }
  .stab.exclstr 0 : { *(.stab.exclstr) }
  .stab.index 0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment 0 : { *(.comment) }
  .debug 0 : { *(.debug) }
  .line 0 : { *(.line) }
  .debug_srcinfo 0 : { *(.debug_srcinfo) }
  .debug_sfnames 0 : { *(.debug_sfnames) }
  .debug_aranges 0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  .debug_info 0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev 0 : { *(.debug_abbrev) }
  .debug_line 0 : { *(.debug_line) }
  .debug_frame 0 : { *(.debug_frame) }
  .debug_str 0 : { *(.debug_str) }
  .debug_loc 0 : { *(.debug_loc) }
  .debug_macinfo 0 : { *(.debug_macinfo) }
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames 0 : { *(.debug_varnames) }
  ._isr_0 exception_base_address + 0x200 + ((vector_size << 5) *0) : { KEEP(*(._isr_0)) } > exception_mem
}
