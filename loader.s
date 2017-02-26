section .__mbHeader             ; multiboot header
align 4

   MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
   FLAGS        equ 0x0            ; multiboot flags
   CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum

   dd MAGIC_NUMBER
   dd FLAGS
   dd CHECKSUM

;;

KERNEL_STACK_SIZE equ 4096
section .bss
align 4

kernel_stack:
   resb KERNEL_STACK_SIZE

;;

section .text:
align 4

global gdt_flush
extern gp

gdt_flush:
   lgdt [gp]
   mov ax, 0x10
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax
   jmp 0x08:flush_cs
flush_cs:
   ret

extern idtp
global idt_load
idt_load:
   lidt [idtp]
   ret

%macro ISR 1
global isr%1
isr%1:
   cli
   push byte %1
   jmp isr_common_stub
%endmacro

; push a dummy onto the stack
; where an error code would go
%macro ISR_DUMMY 1
global isr%1
isr%1:
   cli
   push byte 0x0 ; dummy
   push byte %1
   jmp isr_common_stub
%endmacro

ISR_DUMMY 0
ISR_DUMMY 1
ISR_DUMMY 2
ISR_DUMMY 3
ISR_DUMMY 4
ISR_DUMMY 5
ISR_DUMMY 6
ISR_DUMMY 7
ISR 8
ISR_DUMMY 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR_DUMMY 15
ISR_DUMMY 16
ISR_DUMMY 17
ISR_DUMMY 18
ISR_DUMMY 19
ISR_DUMMY 20
ISR_DUMMY 21
ISR_DUMMY 22
ISR_DUMMY 23
ISR_DUMMY 24
ISR_DUMMY 25
ISR_DUMMY 26
ISR_DUMMY 27
ISR_DUMMY 28
ISR_DUMMY 29
ISR_DUMMY 30
ISR_DUMMY 31

extern fault_handler
isr_common_stub:
   pusha
   push ds
   push es
   push fs
   push gs
   mov ax, 0x10
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov eax, esp   ; Push us the stack
   push eax
   mov eax, fault_handler
   call eax       ; A special call, preserves the 'eip' register
   pop eax
   pop gs
   pop fs
   pop es
   pop ds
   popa
   add esp, 8
   iret

; kernel entry
global loader
loader:
   mov eax, 0xCAFEBABE
   mov esp, kernel_stack + KERNEL_STACK_SIZE

   extern kmain
   call kmain


; vim: set ft=nasm:
