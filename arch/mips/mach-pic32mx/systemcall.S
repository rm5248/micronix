#
# Handle the systemcall generation
#

# C prototype: void systemcall(number)
.text
.type systemcall, @function
.globl systemcall
systemcall:
    move $v0, $a0   # v0 = syscall number. 
                    # this is the return value register, but
                    # seems to be used as the syscall param
    syscall         # generate an interrupt to the processor
    jr $ra          # go back to our calling function
