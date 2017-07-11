%ifndef MEMORY_ASM
%define MEMORY_ASM

; ES:DI - destination
; CX - bytes counter
; AX - value

memset:
	rep stosb
	ret

%endif
