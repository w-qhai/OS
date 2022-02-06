#pragma once

#include <cstdint>
#include "queue.h"

extern char* const vram;
extern const int scrn_w;
extern const int scrn_h;
extern const int g_size;
extern Queue mouse_buff;
extern Queue keyboard_buff;
struct Mouse {
    int button;
    int x, y;
};
extern Mouse mouse;

extern "C" {
    int get_gdt();
    int get_idt();
}

template<class T>
void swap(T& t1, T& t2) {
    T t = t1;
    t1 = t2;
    t2 = t;
}

template<class T>
T max(const T& t1, const T& t2) {
    return t1 > t2 ? t1 : t2;
}

template<class T>
T min(const T& t1, const T& t2) {
    return t1 > t2 ? t2 : t1;
}
