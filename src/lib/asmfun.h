#pragma once

#include <stdint.h>

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