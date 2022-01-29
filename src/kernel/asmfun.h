#pragma once

#include <stdint.h>

struct GDT_Descriptor
{
    uint16_t limit_low, base_low;
    uint8_t base_mid, more_flag;
    uint8_t limit_high, base_hig;
};

struct IDT_Descriptor {
    uint16_t offset_low, selector;
    uint8_t dw_count, more_flags;
    uint16_t offset_high;
};

void set_gdt_seg();

void set_idt_seg(IDT_Descriptor* idt, int offset, int selector, int more_flags);

void mem_set(int addr, int bytes, int data);

void load_gdtr(int limit, int addr);
void load_idtr(int limit, int addr);

void cli();
void sti();
void io_set_flags(int flags);
int io_get_flags();

// in  al/ax/eax port
int in_byte(int port);
int in_word(int port);
int in_dword(int port);

// out port data
void out_byte(int port, int data);
void out_word(int port, int data);
void out_dword(int port, int data);

// 测试内联汇编
void movb(int addr, int data);
