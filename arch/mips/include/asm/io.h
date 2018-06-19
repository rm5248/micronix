#ifndef MIPS_IO_H
#define MIPS_IO_H

#include <micro-os/compiler_types.h>

#define readl(addr)              *((volatile unsigned*)(addr))
#define writel(value,addr)    *(volatile unsigned*)(addr) = value

//*(volatile unsigned*)
/*
#define readb(addr) __raw_readb(*(volatile void*)addr)
#define readw(addr) __raw_readw(*(volatile void*)addr)
#define readl(addr) __raw_readl(*(volatile uint32_t*)addr)

#define writeb(value,addr) __raw_writeb(value,addr)
#define writew(value,addr) __raw_writew(value,addr)
#define writel(value,addr) __raw_writel(value,addr)

static inline uint8_t __raw_readb(const volatile void __iomem *addr)
{
    return *(const volatile uint8_t *)addr;
}

static inline uint16_t __raw_readw(const volatile void __iomem *addr)
{
    return *(const volatile uint16_t *)addr;
}

static inline uint32_t __raw_readl(const uint32_t *addr)
{
    return *(const volatile uint32_t *)addr;
}

static inline void __raw_writeb(uint8_t value, volatile void __iomem *addr)
{
    *(volatile uint8_t*)addr = value;
}

static inline void __raw_writew(uint16_t value, volatile void __iomem *addr)
{
    *(volatile uint16_t*)addr = value;
}

static inline void __raw_writel(uint32_t value, volatile void __iomem *addr)
{
    *(volatile uint32_t*)addr = value;
}
*/

#endif
