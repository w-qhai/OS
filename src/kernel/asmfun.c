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

void movb(int addr, int data) {
    __asm {
        mov     ecx, [esp + 0]
        mov     al, [esp + 4]
        mov     [ecx], al
    }
    // *(char*)addr = data;
}

void set_flags(int flags) {
    __asm {
        mov     eax, [esp]
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

// io_get_flags: // int io_get_flags()
//     pushfd
//     pop     eax
//     ret

// io_set_flags: // void io_set_flags(int flags)
//     mov     eax, [esp + 4]
//     push    eax
//     popfd

//     pop     eax
//     ret

// in_byte:    // int in_byte(int port)
//     mov     edx, [esp + 1]
//     mov     eax, 0
//     in      al, dx

//     pop     eax
//     ret

// in_word:    // int in_word(int port)
//     mov     edx, [esp + 1]
//     mov     eax, 0
//     in      ax, dx

//     pop     eax
//     ret

// in_dword:    // int in_byte(int port)
//     mov     edx, [esp + 1]
//     in      eax, dx

//     pop     eax
//     ret

// out_byte:   // void out_byte(int, port, int data)
//     mov     edx, [esp + 4]
//     mov     eax, [esp + 8]

//     out     dx, al

//     pop     eax
//     pop     eax
//     ret

// out_word:   // void out_byte(int, port, int data)
//     mov     edx, [esp + 4]
//     mov     eax, [esp + 8]

//     out     dx, ax

//     pop     eax
//     pop     eax
//     ret

// out_dword:   // void out_byte(int, port, int data)
//     mov     edx, [esp + 4]
//     mov     eax, [esp + 8]

//     out     dx, eax

//     pop     eaxg
//     ret
