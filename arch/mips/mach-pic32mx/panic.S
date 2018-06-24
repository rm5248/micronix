.globl lowlevel_panic

.text
lowlevel_panic:
    di                  # Disable interrupts
    j lowlevel_panic    # Busy loop back to our lowlevel_panic
    nop                 # Delay slot
