#pragma once

#include <stdint.h>

struct GDT_Descriptor
{
    uint16_t limit_low, base_low;
    uint8_t base_mid, more_flags;
    uint8_t limit_high, base_high;
};

struct IDT_Descriptor {
    uint16_t offset_low, selector;
    uint8_t dw_count, more_flags;
    uint16_t offset_high;
};

void set_gdt_seg(GDT_Descriptor* gdt, int limit, int base, int more_flags);
void set_idt_seg(IDT_Descriptor* idt, int offset, int selector, int more_flags);

extern "C" {
    void cli();
    void sti();
    void set_flags(int flags);
    int get_flags();

    // in  al/ax/eax port
    int in_byte(int port);

    // out port data
    void out_byte(int port, int data);

    void set_cr0(int cr0);
    int get_cr0();

    void load_tr(int tr);
    void switch_task(int eip, int cs);
}