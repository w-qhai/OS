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

// _load_gdtr:		; void load_gdtr(int limit, int addr);
// 		MOV		AX,[ESP+4]		; limit
// 		MOV		[ESP+6],AX
// 		LGDT	[ESP+6]
// 		RET

// _load_idtr:		; void load_idtr(int limit, int addr);
// 		



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
        mov     ecx, [ebp + 8]
        mov     al, [ebp + 12]
        mov     [ecx], al
    }
    // *(char*)addr = data;
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
