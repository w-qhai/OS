#pragma once

#include "constants.h"
#include "asmfun.h"
#include "graphics.h"
#include "fonts.h"

extern bool is_mouse_init; 

void enable_mouse();
void mouse_decode(const int8_t data[]);
// void response_mouse();

extern "C" {
    // 中断发生，先调用汇编中的中断处理程序，汇编再调用C函数
    extern void asm_response_mouse();
    void response_mouse();
}
