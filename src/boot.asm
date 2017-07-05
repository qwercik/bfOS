[BITS 16]
[ORG 0x7C00]

jmp start

%include "bpb.asm"

start:
	jmp word 0x0000:reload_cs

reload_cs:
	; Set up data segment registers
	xor ax, ax
	mov ds, ax

	mov ax, 0x1000
	mov es, ax

	; Set up stack (4 KiB)
	mov ax, 0x06C0
	mov ss, ax
	mov sp, 0x1000
	
	; Clear screen
	mov ax, 3
	int 0x10
	
	; Set up loops counter
	xor cx, cx

	; ES:DI is array pointer
	; ES = 0x1000
	xor di, di
	
	; DS:SI is code pointer
	; DS = 0x0000
	mov si, source_code

	call bf_interpreter

	jmp $

source_code db "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.", 0

%include "bf.asm"

%if ($ - $$) > 510
	%error "Too much code!"
%endif

times 510 - ($ - $$) db 0
dw 0xAA55
