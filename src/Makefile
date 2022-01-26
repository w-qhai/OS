AS	=	nasm
VM1	=	qemu-system-i386
VM2	=	bochs
CC	= 	clang
DEL	= 	rm

BOOTDIR	= ./boot
KERNEDIR= ./kernel
IMAGE   = PianOS.img



$(IMAGE): $(BOOTDIR)/bootsect.bin	$(BOOTDIR)/setup.bin $(BOOTDIR)/head.bin	
# 1.44MB 可在bochs中使用，以便调试
	@dd if=/dev/zero    			of=PianOS.img   bs=1474560	count=1 	2>>/dev/null
	@dd if=$(BOOTDIR)/bootsect.bin	of=PianOS.img   bs=512 		count=1 conv=notrunc 2>>/dev/null
	@dd	if=$(BOOTDIR)/setup.bin		of=PianOS.img	bs=512 		count=4 seek=1 conv=notrunc 2>>/dev/null
	@dd	if=$(BOOTDIR)/head.bin		of=PianOS.img	bs=512 		seek=5 	conv=notrunc 2>>/dev/null
	-@echo "\e[01;32m[Bulid Successfully]\e[00m"

$(BOOTDIR)/%.bin: $(BOOTDIR)/%.asm
	$(AS) $^ -o $@ 

$(BOOTDIR)/head.bin: $(BOOTDIR)/head.asm  $(KERNEDIR)/kernel.asm
	$(AS) $(BOOTDIR)/head.asm -o $@ -l $(KERNEDIR)/kernel.lst

$(KERNEDIR)/kernel.asm: $(KERNEDIR)/main.o $(KERNEDIR)/fonts.o 
	ld -m elf_i386 -r -s $^ -o $(KERNEDIR)/pre_kernel.o
	@../tools/objconv -np:.: $(KERNEDIR)/pre_kernel.o $(KERNEDIR)/kernel.o	>/dev/null
	@../tools/objconv -fnasm $(KERNEDIR)/kernel.o	>/dev/null
	@sed -i -e 's/[a-z]*execute//g' -e 's/: *function//g' $(KERNEDIR)/kernel.asm

$(KERNEDIR)/asmfun.o: $(KERNEDIR)/asmfun.c
	$(CC) -c -fasm-blocks -m32 $^ -o $@

$(KERNEDIR)/%.o: $(KERNEDIR)/%.cc
	$(CC) -m32 -c $^ -o $@


run : PianOS.img
	$(VM1) -drive format=raw,if=floppy,file=$(IMAGE)  

qemu : PianOS.img
	$(VM1) -drive format=raw,if=floppy,file=$(IMAGE)
bochs: PianOS.img
	$(VM2)	-f bochsrc.txt

clean:
	-$(DEL)	PianOS.img
	-$(DEL)	$(BOOTDIR)/*.bin
	-$(DEL)	$(KERNEDIR)/*.o
	-$(DEL)	$(KERNEDIR)/kernel.asm
	-$(DEL)	$(KERNEDIR)/kernel.lst

#gcc -s -c a.c -m32 -fno-asynchronous-unwind-tables -fno-pie -fcf-protection=none -mmanual-endbr; ./objconv a.o -fnasm