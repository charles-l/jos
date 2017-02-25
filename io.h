#ifndef IO_H
#define IO_H

extern void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);

//// FRAMEBUFFER ////
#define FB_GREEN     2
#define FB_DARK_GREY 8
#define FB_MAXPOS    2000

void puts(char *s);
void puti(int i, int base);
void printf(char *fmt, ...);

// helper
void fb_clear();

// low-level
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void fb_cmv(unsigned short pos);
void fb_pchar(char c);
int fb_cpos();

//// SERIAL ////
#define SERIAL_COM1_BASE                0x3F8      /* COM1 base port */

// helper
void serial_write(char *s);

// low-level
void serial_configure_baud_rate(unsigned short com, unsigned short divisor);
void serial_configure_line(unsigned short com);


#endif // IO_H
