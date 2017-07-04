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
	inc di	
	jmp bf_interpreter

bf_left:
	dec di
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
	mov ah, 0xE
	mov bx, 0x0007
	int 0x10
	jmp bf_interpreter

bf_get_char:
	xor ax, ax
	int 0x16
	mov byte [es:di], al
	jmp bf_interpreter

bf_loop_start:
	inc cx

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
		cmp al, ']'
		je .end_of_loop_char
		jmp .ptr_zero

		.end_of_loop_char:
			dec cx

			cmp cx, 0
			je .matching_loop_end
			jmp .ptr_zero

			.matching_loop_end:
				dec si
				jmp bf_interpreter

bf_loop_end:
	dec cx

	mov bl, byte [es:di]
	cmp bl, 0
	je .ptr_zero
	
	.ptr_non_zero:
		pop si
		jmp bf_interpreter

	.ptr_zero:
		add sp, 2
		jmp bf_interpreter