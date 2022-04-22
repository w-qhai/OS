#include "asmfun.h"

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
