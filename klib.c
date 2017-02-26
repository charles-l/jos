#include "klib.h"
#include "io.h"

void puts(char *s) {
    for(u32 i = 0; s[i] != '\0'; i++) {
        fb_pchar(s[i]);
    }
}

void putui(u32 i, int base) {
    if(i > 0) {
        putui(i / base, base);
        int j = i % base;
        fb_pchar(j + (j < 10 ? '0' : 'A' - 10));
    }
}

void puti(int i, int base) {
    if(i == 0) {
        fb_pchar('0');
    } else if (i < 0) {
        fb_pchar('-');
        putui(-i, base);
    } else {
        putui(i, base);
    }
}

void printf(char *fmt, ...) {
    __builtin_va_list argp;
    __builtin_va_start(argp, fmt);
    for(char *p = fmt; *p != '\0'; p++) {
        if(*p == '%') {
            switch(*++p) {
                case 'c':
                    fb_pchar(__builtin_va_arg(argp, int));
                    break;
                case 's':
                    puts(__builtin_va_arg(argp, char *));
                    break;
                case 'i':
                    puti(__builtin_va_arg(argp, int), 10);
                    break;
                case 'x':
                    puti(__builtin_va_arg(argp, int), 16);
                    break;
                case 'b':
                    puti(__builtin_va_arg(argp, int), 2);
                    break;
                case '%':
                    fb_pchar('%');
                    break;
            }
        } else {
            fb_pchar(*p);
        }
    }
    __builtin_va_end(argp);
}

void *memset(u8 *d, u8 f, size_t n) {
    for(u32 i = 0; i < n; i++) {
        d[i] = f;
    }
    return d;
}
