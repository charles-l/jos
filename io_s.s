global outb

outb:
	mov al, [esp + 8]
	mov dx, [esp + 4]
	out dx, al
	ret

; vim: set ft=nasm:

global inb

inb:
	mov dx, [esp + 4]
	in  al, dx
	ret
