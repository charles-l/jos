#ifndef IDT_H
#define IDT_H
#include "type.h"

struct idt_entry {
    u16 base_lo;
    u16 sel;
    u8  _;
    u8  flags;
    u16 base_hi;
} __attribute__((packed));

struct idt_p {
    u16 size;
    u32 address;
} __attribute__((packed));

struct regs {
    u32 gs, fs, es, ds;
    u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    u32 int_no, err_code;
    u32 eip, cs, eflags, useresp, ss;
};

struct idt_entry idt[256];
struct idt_p idtp;

void idt_set_gate(u8 i, u32 base, u16 sel, u8 flags);
void idt_install();

extern void idt_load();

void isrs_install();
void fault_handler(struct regs *r);

#endif // IDT_H
