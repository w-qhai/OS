#pragma once

#include "../lib/asmfun.h"
#include "../lib/queue.hpp"

struct Mouse {
    int button;
    int x, y;
};
#define MOUSE_BUFF_SIZE 3*128
extern Mouse mouse;
extern bool is_mouse_init;
extern Queue<uint8_t, MOUSE_BUFF_SIZE> mouse_buff;

void enable_mouse();
void mouse_decode(const int8_t data[]);
// void response_mouse();

extern "C" {
    // 中断发生，先调用汇编中的中断处理程序，汇编再调用C函数
    extern void asm_response_mouse();
    void response_mouse();
}
