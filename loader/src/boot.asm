[BITS 16]
[ORG 0x7C00]

jmp word 0x0000:start

start:
	; Set up stack (4 KiB)
	mov ax, 0x06C0
	mov ss, ax
	mov sp, 0x1000
	
	call clear_screen

	; Reading brainfuck code to memory

	; Set data buffer (ES:BX) to 0x07E0:0x0000
	mov bx, 0x07E0
	mov es, bx
	xor bx, bx

	; Set up interrupt parameters
	mov ah, 2
	xor ch, ch
	mov cl, 2
	xor dh, dh
	dd 0x00BFC0DE ; BfToFloppy replace this flag with setting amount of sectors to read
	int 0x13

	jc read_error

	call bf_interpreter
	jmp $

read_error:
	xor ax, ax
	mov ds, ax
	mov si, msg_read_error
	call print_string
	jmp $

msg_read_error db "Couldn't read brainfuck code", 0

%include "screen.asm"
%include "bf.asm"

%if ($ - $$) > 510
	%error "Too much code!"
%endif

times 510 - ($ - $$) db 0
dw 0xAA55
