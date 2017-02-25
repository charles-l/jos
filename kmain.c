#include "io.h"

void kmain() {
    fb_clear();

    char *a = "hello world!\n";
    puts(a);
    printf("hi %c %s '%i' %i %i %x %b %%", 'd', "a test", 123, -2020, 0, 0xFF, 1313);

    serial_configure_baud_rate(SERIAL_COM1_BASE, 0x03);
    serial_configure_line(SERIAL_COM1_BASE);
    serial_write("Hi");

    while(1) {
        // kernel main loop
    }
}
