#include "asmfun.h"

void set_gdt_seg() {
    
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

void set_flags(int flags) {
    __asm {
        mov     eax, [ebp + 8]
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
        mov     edx, [ebp + 8]
        mov     eax, 0
        in      ax, dx
    }
}

void out_byte(int port, int data) {
    __asm {
        mov     edx, [ebp + 8]
        mov     eax, [ebp + 12]
        out     dx, al
    }
}
