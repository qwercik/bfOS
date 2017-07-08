%ifndef SCREEN_ASM
%define SCREEN_ASM

clear_screen:
	mov ax, 3
	int 0x10
	ret

print_char:
	mov ah, 0xE
	xor bh, bh
	mov bl, 0x07
	int 0x10

	; Code for "change" CRLF to LF
	cmp al, 0xA
	jne .end
	mov al, 0xD
	call print_char

	.end:
		ret

print_string:
	lodsb 
	cmp al, 0
	je .end
		call print_char
		jmp print_string
	.end:
		ret

%endif
