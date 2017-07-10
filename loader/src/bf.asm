%ifndef BF_ASM
%define BF_ASM

DATA_ARRAY_SIZE equ 30000

bf_interpreter:
	; DS:SI is pointer to code
	lodsb
	cmp al, 0
	je .end
		cmp al, '>'
			je bf_right
		cmp al, '<'
			je bf_left
		cmp al, '+'
			je bf_plus
		cmp al, '-'
			je bf_minus
		cmp al, '.'
			je bf_print_char
		cmp al, ','
			je bf_get_char
		cmp al, '['
			je bf_loop_start
		cmp al, ']'
			je bf_loop_end
	
		jmp bf_interpreter		
	.end:
		ret

bf_right:
	cmp di, DATA_ARRAY_SIZE - 1
	je .end
		inc di
	.end:
		jmp bf_interpreter

bf_left:
	cmp di, 0
	je .end
		dec di
	.end:
		jmp bf_interpreter

bf_plus:
	mov bl, byte [es:di]
	inc bl
	mov byte [es:di], bl
	jmp bf_interpreter

bf_minus:
	mov bl, byte [es:di]
	dec bl
	mov byte [es:di], bl
	jmp bf_interpreter

bf_print_char:
	mov al, byte [es:di]
	call print_char
	jmp bf_interpreter

bf_get_char:
	xor ax, ax
	int 0x16
	mov byte [es:di], al
	jmp bf_interpreter

bf_loop_start:
	mov bl, byte [es:di]
	cmp bl, 0
	je .ptr_zero

	.ptr_non_zero:
		dec si
		push si
		inc si
		jmp bf_interpreter

	.ptr_zero:
		lodsb
		cmp cx, 0
		jne .check_characters
		cmp al, ']'
		je bf_interpreter

		.check_characters:
			cmp al, '['
			je .start_of_loop_char
			cmp al, ']'
			je .end_of_loop_char
			jmp .ptr_zero

			.start_of_loop_char:
				inc cx
				jmp .ptr_zero

			.end_of_loop_char:
				dec cx
				jmp .ptr_zero
		
bf_loop_end:
	mov bl, byte [es:di]
	cmp bl, 0
	je .ptr_zero

	.ptr_non_zero:
		pop si
		jmp bf_interpreter

	.ptr_zero:
		add sp, 2
		jmp bf_interpreter

%include "screen.asm"

%endif
