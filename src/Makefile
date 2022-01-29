AS	=	nasm
VM1	=	qemu-system-i386
VM2	=	bochs
CC	= 	clang
DEL	= 	rm

BOOTDIR	= ./boot
KERNEDIR= ./kernel
BINDIR  = ./bin
IMAGE   = PianOS.img




$(IMAGE): $(BINDIR)/bootsect.bin $(BINDIR)/setup.bin $(BINDIR)/head.bin	
# 1.44MB 可在bochs中使用，以便调试
	@dd if=/dev/zero    			of=PianOS.img   bs=1474560	count=1 	2>>/dev/null
	@dd if=$(BINDIR)/bootsect.bin	of=PianOS.img   bs=512 		count=1 conv=notrunc 2>>/dev/null
	@dd	if=$(BINDIR)/setup.bin		of=PianOS.img	bs=512 		count=4 seek=1 conv=notrunc 2>>/dev/null
	@dd	if=$(BINDIR)/head.bin		of=PianOS.img	bs=512 		seek=5 	conv=notrunc 2>>/dev/null
	-@echo "\e[01;32m[Bulid Successfully]\e[00m"

$(BINDIR)/%.bin: $(BOOTDIR)/%.asm
	$(AS) $^ -o $@ 

$(BINDIR)/head.bin: $(BOOTDIR)/head.asm  $(KERNEDIR)/kernel.asm
	$(AS) $(BOOTDIR)/head.asm -o $@ -l $(BINDIR)/kernel.lst

$(KERNEDIR)/kernel.asm: $(BINDIR)/constants.o $(BINDIR)/main.o $(BINDIR)/fonts.o $(BINDIR)/asmfun.o $(BINDIR)/graphics.o
	ld -m elf_i386 -r -s $^ -o $(BINDIR)/pre_kernel.o
	@../tools/objconv -np:.: $(BINDIR)/pre_kernel.o $(BINDIR)/kernel.o	>/dev/null
	@../tools/objconv -fnasm $(BINDIR)/kernel.o	>/dev/null
	@sed -i -e 's/[a-z]*execute//g' -e 's/: *function//g' $(BINDIR)/kernel.asm

$(BINDIR)/asmfun.o: $(KERNEDIR)/asmfun.cc
	$(CC) -c -fasm-blocks -m32 $^ -o $@

$(BINDIR)/%.o: $(KERNEDIR)/%.cc
	$(CC) -m32 -g -c $^ -o $@ 
#	$(CC) -m32 -fno-asynchronous-unwind-tables -fno-pie -fcf-protection=none -mmanual-endbr -c $^ -o $@

run : PianOS.img
	$(VM1) -drive format=raw,if=floppy,file=$(IMAGE)  

qemu : PianOS.img
	$(VM1) -drive format=raw,if=floppy,file=$(IMAGE)
bochs: PianOS.img
	$(VM2)	-f bochsrc.txt

clean:
	-$(DEL)	PianOS.img
	-$(DEL) $(BINDIR)/*

#gcc -s -c a.c -m32 -fno-asynchronous-unwind-tables -fno-pie -fcf-protection=none -mmanual-endbr; ./objconv a.o -fnasm