#include "io.h"
#include "type.h"
#include "boot.h"
#include "idt.h"
#include "klib.h"

void kmain() {
    gdt_load();

    idt_install();
    isrs_install();

    fb_clear();
    char *a = "hello world!\n";
    puts(a);
    printf("hi %x", 0xBEEF);

    serial_configure_baud_rate(SERIAL_COM1_BASE, 0x03);
    serial_configure_line(SERIAL_COM1_BASE);
    serial_write("Hi\n");

    u8 i = 0;
    printf("-> %i\n", 1/i);

    while(1) {
        // kernel main loop
    }
}
