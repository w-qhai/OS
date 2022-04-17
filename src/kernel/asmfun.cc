#include "asmfun.h"

void set_gdt_seg(GDT_Descriptor* gdt, int limit, int base, int more_flags) {
    gdt->limit_low  = limit & 0xffff;
    gdt->base_low   = base & 0xffff;
    gdt->base_mid   = (base>>16) & 0xff;
    gdt->more_flags  = more_flags & 0xff;
    gdt->limit_high = ((limit>>16) & 0x0f) | ((more_flags>>8) & 0xf0);
    gdt->base_high  = (base>>24) & 0xff;
}

void set_idt_seg(IDT_Descriptor* idt, int offset, int selector, int more_flags) {
    idt->offset_low  = offset & 0xffff;
    idt->selector    = selector;
    idt->dw_count    = (more_flags >> 8) &0xff;
    idt->more_flags  = (more_flags) & 0xff;
    idt->offset_high = (offset >> 16) & 0xffff;
}

void cli() {
    __asm {
        cli
    }
}

void sti() {
    __asm {
        sti
    }
}

void set_flags(int flags_) {
    __asm {
        mov     eax, flags_
        push    eax
        popfd   
    }
}

int get_flags() {
    __asm {
        pushfd
        pop     eax
        ret
    }
}

int in_byte(int port) {
    __asm {
        mov     edx, port
        mov     eax, 0
        in      al, dx
    }
}

void out_byte(int port, int data) {
    __asm {
        mov     edx, port
        mov     eax, data
        out     dx, al
    }
}

void set_cr0(int cr0_) {
    __asm {
        mov     eax, cr0_
        mov     cr0, eax
    }
}

int get_cr0() {
    __asm {
        mov     eax, cr0
    }
}

void load_tr(int tr_) {
    __asm {
        ltr     tr_
    }
}
