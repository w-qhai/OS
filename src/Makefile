AS	=	nasm
VM1	=	qemu-system-i386
VM2	=	bochs
CC	= 	clang
DEL	= 	rm

OPTS    = -m32 -fasm-blocks -c -W -fno-use-linker-plugin
BOOTDIR	= ./boot
KERNEDIR= ./kernel
BINDIR  = ../bin
IMAGE   = PianOS.img

OBJS = 	$(BINDIR)/constants.o $(BINDIR)/main.o \
		$(BINDIR)/fonts.o $(BINDIR)/asmfun.o \
		$(BINDIR)/graphics.o $(BINDIR)/int.o \
		$(BINDIR)/queue.o \
		$(BINDIR)/mouse.o $(BINDIR)/keyboard.o \
		$(BINDIR)/memory.o 		$(BINDIR)/layer.o \
		$(BINDIR)/window.o 

$(IMAGE): $(BINDIR)/bootsect.bin $(BINDIR)/setup.bin $(BINDIR)/head.bin $(OBJS) Makefile
# 1.44MB 可在bochs中使用，以便调试
	ld $(BINDIR)/head.bin $(OBJS) -e start -melf_i386 -Ttext 0x0 -o $(BINDIR)/PianOS.sys
	@cp $(BINDIR)/PianOS.sys $(BINDIR)/PianOS.syss
	@objcopy -O binary $(BINDIR)/PianOS.sys
	@dd if=/dev/zero    			of=PianOS.img   bs=1474560	count=1 	2>>/dev/null
	@dd if=$(BINDIR)/bootsect.bin	of=PianOS.img   bs=512 		count=1 conv=notrunc 2>>/dev/null
	@dd if=$(BINDIR)/setup.bin		of=PianOS.img	bs=512 		count=4 seek=1 conv=notrunc 2>>/dev/null
	@dd if=$(BINDIR)/PianOS.sys		of=PianOS.img	bs=512 		seek=5 	conv=notrunc 2>>/dev/null
	-@echo "\e[01;32m[Build Successfully]\e[00m"

$(BINDIR)/%.bin: $(BOOTDIR)/%.asm Makefile
	$(AS) $< -o $@ 

$(BINDIR)/head.bin: $(BOOTDIR)/head.asm Makefile
	$(AS) -felf32 $(BOOTDIR)/head.asm -o $(BINDIR)/head.bin

$(BINDIR)/asmfun.o: $(KERNEDIR)/asmfun.cc Makefile
	$(CC) $(OPTS) $< -o $@ 

$(BINDIR)/main.o: $(KERNEDIR)/main.cc Makefile
	g++ -fno-stack-protector -m32 -fno-asynchronous-unwind-tables -fno-use-cxa-atexit -fno-pie -fcf-protection=none -mmanual-endbr -c $< -o $@

$(BINDIR)/%.o: $(KERNEDIR)/%.cc $(KERNEDIR)/%.h Makefile
# 	$(CC) $(OPTS) $< -o $@ 
# 	g++ -fno-stack-protector -m32 -fno-asynchronous-unwind-tables -fno-use-cxa-atexit -fno-pie -fcf-protection=none -mmanual-endbr -c $< -o $@
	g++ -m32 -fno-use-cxa-atexit -nostdlib -c $< -o $@

run : Makefile $(IMAGE) Makefile
	$(VM1) -drive format=raw,if=floppy,file=$(IMAGE) -m 4G -vga std
qemu : Makefile $(IMAGE) Makefile
	$(VM1) -drive format=raw,if=floppy,file=$(IMAGE)
bochs: Makefile $(IMAGE) Makefile
	$(VM2)	-f bochsrc.txt

debug:
	$(VM1) -S -s -fda $(IMAGE) -boot a &
	sleep 1
	gdb -x gdb.script

clean: Makefile
	-$(DEL)	$(IMAGE)
	-$(DEL) $(BINDIR)/*

#gcc -s -c a.c -m32 -fno-asynchronous-unwind-tables -fno-pie -fcf-protection=none -mmanual-endbr; ./objconv a.o -fnasm