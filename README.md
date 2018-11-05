Micronix Kernel

License: GPL v2 Only

This project uses some headers from the Linux kernel.
It also has some roots in the RetroBSD project(linker script)

It also contains ideas learned in 4003-506 class of 20103
at RIT.  Thanks to the professors at RIT for giving ideas
on the basic OS data structures and initialization

Note that this kernel borrows a lot from Linux, specifically the
initialization process.  The kernel does not have a device tree
like Linux, due to the fact that it is designed for microcontrollers.
If you look at Linux(version 3.4) you can see the same structure
for initializing boards.
