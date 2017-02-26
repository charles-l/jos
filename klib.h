#ifndef KLIB_H
#define KLIB_H

#include "type.h"

void puts(char *s);
void printf(char *fmt, ...);
void ser_puts(char *s);

void *memset(u8 *d, u8 f, size_t n);

#endif // KLIB_H
