# bfOS
bfOS is a project of bootable brainfuck interpreter for x86 architecture. You can use it for developing your own operating system, in brainfuck ;)

## Details
This repository contains:
- loader - written in x86 Assembly bootable brainfuck interpreter.
- BfToFloppy - written in C++ tool, that converts brainfuck code into a floppy disk image (1,44MB). It's cross-platform, so you can use it on Linux, BSD, Windows and other OS. I'll use Linux.
- kernel - written in brainfuck an example kernel (current example has been generated with copy.sh text-to-brainfuck utility)

## Build
If you want to use an existing binary package, you can skip this step.
First, you have to get a copy of this repository. You can download a zip file with source, or clone it with git.

```bash
$ git clone https://github.com/qwercik/bfOS
$ cd bfOS
```

Then, you have to build a loader. It's relatively easy.

```bash
$ cd loader
$ make
```
You should get a file loader.bin. It will be neccessary later.

Now, you have to build an image tool. You can do this in this way:

```bash
$ cd BfToFloppy
$ cmake .
$ make
```

You should get a file BfToFloppy.

## Usage
First, you must make a new working directory and copy BfToFloppy and loader.bin to it.

Now, you can create an example file with brainfuck code. You can name it on your own. I'll use the name **code.bf**. You can also use an example bfOS kernel (kernel/kernel.bf).

Then, type the following command:

```bash
$ ./BfToFloppy floppy.img code.bf
```

If you are using Windows, type in cmd:
```bash
BfToFloppy.exe floppy.img code.bf
```

You should get file floppy.img. It's floppy image file. You can boot from this in virtual machine, like Bochs, QEMU or VirtualBox. You can also write this to real floppy disk or pendrive and boot on your real hardware.

Good luck developing your OS in brainfuck ;)

# Acknowledgements
- Patrycjerz
