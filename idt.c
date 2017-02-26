#include "idt.h"
#include "klib.h"

void idt_set_gate(u8 i, u32 base, u16 sel, u8 flags) {
    idt[i].base_lo = (base & 0xFFFF);
    idt[i].base_hi = ((base >> 16) & 0xFFFF);
    idt[i].sel = sel;
    idt[i]._ = 0;
    idt[i].flags = flags;
}

void idt_install() {
    idtp.size = (sizeof(struct idt_entry) * 256) - 1;
    idtp.address = (u32) &idt;

    memset((u8 *) &idt, 0, sizeof(struct idt_entry) * 256);

    idt_load();
}
