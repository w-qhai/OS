#pragma once

#include "constants.h"
#include "asmfun.h"
#include "graphics.h"
#include "fonts.h"

void init_keyboard();
extern "C" {
    // 中断发生，先调用汇编中的中断处理程序，汇编再调用C函数
    extern void asm_response_keyboard();
    void response_keyboard();
}
