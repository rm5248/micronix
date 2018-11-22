#ifndef MICRONIX_PRINTK_H
#define MICRONIX_PRINTK_H

#include <generated/autoconf.h>

#define no_printk(msg,...) \
{ if(0) printk(msg, ##__VA_ARGS__); }

#ifdef CONFIG_ENABLE_PRINTK
int printk(const char* message, ...);
#else
#define printk(msg,...)
#endif


#ifndef pr_fmt
#define pr_fmt(fmt) fmt
#endif

/*
 * Levels, if ever implemented.
 */
#define KERN_EMERG
#define KERN_ALERT
#define KERN_CRIT
#define KERN_ERR
#define KERN_WARNING
#define KERN_NOTICE
#define KERN_INFO
#define KERN_DEBUG

/*
 * Macros for Linux compatibility
 */
#define pr_emerg(fmt, ...) \
        printk(KERN_EMERG pr_fmt(fmt), ##__VA_ARGS__)
#define pr_alert(fmt, ...) \
        printk(KERN_ALERT pr_fmt(fmt), ##__VA_ARGS__)
#define pr_crit(fmt, ...) \
        printk(KERN_CRIT pr_fmt(fmt), ##__VA_ARGS__)
#define pr_err(fmt, ...) \
        printk(KERN_ERR pr_fmt(fmt), ##__VA_ARGS__)
#define pr_warning(fmt, ...) \
        printk(KERN_WARNING pr_fmt(fmt), ##__VA_ARGS__)
#define pr_warn pr_warning
#define pr_notice(fmt, ...) \
        printk(KERN_NOTICE pr_fmt(fmt), ##__VA_ARGS__)
#define pr_info(fmt, ...) \
        printk(KERN_INFO pr_fmt(fmt), ##__VA_ARGS__)

#ifdef DEBUG
#define pr_debug(fmt, ...) \
        printk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#else
#define pr_debug(fmt, ...) \
        no_printk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)
#endif

#endif
