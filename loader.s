global loader                   ; the entry symbol for ELF

section .__mbHeader             ; multiboot header
align 4

   MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
   FLAGS        equ 0x0            ; multiboot flags
   CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum

   dd MAGIC_NUMBER
   dd FLAGS
   dd CHECKSUM

;;

section .text:
align 4

loader:
   mov eax, 0xCAFEBABE
   mov esp, kernel_stack + KERNEL_STACK_SIZE

   extern kmain
   call kmain

;;

KERNEL_STACK_SIZE equ 4096
section .bss
   align 4
   kernel_stack:
   resb KERNEL_STACK_SIZE


; vim: set ft=nasm:
