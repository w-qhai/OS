#pragma once

#include <cstdint>

extern char* const vram;
extern const int scrn_w;
extern const int scrn_h;
extern const int g_size;

extern "C" {
    int get_gdt();
    int get_idt();
}
