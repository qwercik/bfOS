ASM = nasm
ASM_PARAMS = -i src/

all: loader.bin

loader.bin: src/boot.asm
	$(ASM) -o $@ $^ $(ASM_PARAMS)

clean:
	rm loader.bin

