ASM = nasm
ASM_PARAMS = -i src/

all: bfOS.img

bfOS.img: src/boot.asm
	$(ASM) -o $@ $^ $(ASM_PARAMS)

clean:
	rm bfOS.img

