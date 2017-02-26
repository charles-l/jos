#include "boot.h"
#include "type.h"

struct gdt_p {
    u16 size;
    u32 address;
} __attribute__((packed));

struct gdt_entry {
    u16 limit_low;
    u16 base_low;
    u8  base_middle;
    u8  access;
    u8  granularity;
    u8  base_high;
} __attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_p gp;

extern void gdt_flush();
void gdt_set_gate(i32 i, u32 base, u32 limit, u8 access, u8 gran) {
    gdt[i].base_low = (base & 0xFFFF);
    gdt[i].base_middle = (base >> 16) & 0xFF;
    gdt[i].base_high = (base >> 24) & 0xFF;

    gdt[i].limit_low = (limit & 0xFFFF);
    gdt[i].granularity = ((limit >> 16) & 0x0F);

    gdt[i].granularity |= (gran & 0xF0);
    gdt[i].access = access;
}

void gdt_load() {
    gp.size = (sizeof(struct gdt_entry) * 3) - 1;
    gp.address = (u32) &gdt;

    gdt_set_gate(0, 0, 0, 0, 0);

    // overlapping code/data segments for now 'cause i don't care

    // code segment
    gdt_set_gate(1, 0, 0xFFFF, 0x9A, 0xCF);

    // data segment
    gdt_set_gate(2, 0, 0xFFFF, 0x92, 0xCF);
    gdt_flush();
}

