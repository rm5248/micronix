#
# Handle the systemcall generation
#

# C prototype: void systemcall0(number)
.text
.type systemcall0, @function
.globl systemcall0
systemcall0:
    move $v0, $a0   # v0 = syscall number. 
                    # this is the return value register, but
                    # seems to be used as the syscall param
    syscall         # generate an interrupt to the processor
    jr $ra          # go back to our calling function
.end systemcall0

# C prototype: void systemcall1(number)
.text
.type systemcall1, @function
.globl systemcall1
systemcall1:
    move $v0, $a0   # v0 = syscall number. 
                    # this is the return value register, but
                    # seems to be used as the syscall param
    syscall         # generate an interrupt to the processor
    jr $ra          # go back to our calling function
.end systemcall1

# C prototype: void systemcall1(number)
.text
.type systemcall2, @function
.globl systemcall2
systemcall2:
    move $v0, $a0   # v0 = syscall number. 
                    # this is the return value register, but
                    # seems to be used as the syscall param
    syscall         # generate an interrupt to the processor
    jr $ra          # go back to our calling function
.end systemcall2

# C prototype: void systemcall1(number)
.text
.type systemcall3, @function
.globl systemcall3
systemcall3:
    move $v0, $a0   # v0 = syscall number. 
                    # this is the return value register, but
                    # seems to be used as the syscall param
    syscall         # generate an interrupt to the processor
    jr $ra          # go back to our calling function
.end systemcall3
