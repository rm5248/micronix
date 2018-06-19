# PIC32MX startup bootstrap
# Based off of RetroBSD and Microchip sources

.set    noreorder
.set    mips32r2
.set    nomips16
.extern main
.extern u_end

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

.end
