#ifndef IO_H
#define IO_H
#include "type.h"

extern void outb(u16 port, u8 data);
u8 inb(u16 port);

//// FRAMEBUFFER ////
#define FB_GREEN     2
#define FB_DARK_GREY 8
#define FB_MAXPOS    2000

void puts(char *s);
void puti(i32 i, i32 base);
void printf(char *fmt, ...);

// helper
void fb_clear();

// low-level
void fb_write_cell(u32 i, char c, u8 fg, u8 bg);
void fb_cmv(u16 pos);
void fb_pchar(char c);
i32 fb_cpos();

//// SERIAL ////
#define SERIAL_COM1_BASE                0x3F8      /* COM1 base port */

// helper
void serial_write(char *s);

// low-level
void serial_configure_baud_rate(u16 com, u16 divisor);
void serial_configure_line(u16 com);


#endif // IO_H
