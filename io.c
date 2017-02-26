#include "io.h"

#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

static int pos = 0;
char *fb = (char *) 0x000B8000;

void fb_cmv(u16 p) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((p >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    p & 0x00FF);
    pos = p;
}

int fb_cpos() {
    return pos;
}

void fb_clear() {
    fb_cmv(0);
    for(int i = 0; i < FB_MAXPOS; i++) {
        fb_pchar(' ');
    }
    fb_cmv(0);
}


void fb_write_cell(u32 i, char c, u8 fg, u8 bg) {
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_pchar(char c) {
    // TODO: add scrolling
    switch(c) {
        case '\n':
            fb_cmv((1 + (fb_cpos() / 80)) * 80); // next line
            break;
        default:
            fb_write_cell(pos++ * 2, c, FB_GREEN, FB_DARK_GREY);
            break;
    }
}


/// SERIAL PORT

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)
#define SERIAL_LINE_ENABLE_DLAB         0x80

void serial_configure_baud_rate(unsigned short com, unsigned short divisor) {
    outb(SERIAL_LINE_COMMAND_PORT(com),
            SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com),
            (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com),
            divisor & 0x00FF);
}

void serial_configure_line(unsigned short com) {
    /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
     * Content: | d | b | prty  | s | dl  |
     * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
     */
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(u32 com) {
    /* 0x20 = 0010 0000 */
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_write(char *s) {
    for(int i = 0; s[i] != '\0'; i++) {
        outb(SERIAL_COM1_BASE, s[i]);
    }
}

