#ifndef MICRONIX_CONSOLE_H
#define MICRONIX_CONSOLE_H

struct console {
    char    name[16];
    void    (*write)(struct console *, const char *, unsigned);
    void*   data;
};

void console_set(struct console*);
void console_write(const char* data);

#endif
