#pragma once
#include <cstdint>
#include "asmfun.h"
#include "constants.h"
#include "graphics.h"
#include "fonts.h"

void init_keyboard_mouse();

extern "C" {
    // 中断发生，先调用汇编中的中断处理程序，汇编再调用C函数
    extern void asm_response_keyboard();
    void response_keyboard();

    extern void asm_response_mouse();
    void response_mouse();
}
