#pragma once

#include "../lib/asmfun.h"
#include "../lib/queue.hpp"

#define KEYBOARD_BUFF_SIZE 128
extern char key_table[0x54];
extern Queue<uint8_t, KEYBOARD_BUFF_SIZE> keyboard_buff;

void init_keyboard();
extern "C" {
    // 中断发生，先调用汇编中的中断处理程序，汇编再调用C函数
    extern void asm_response_keyboard();
    void response_keyboard();
}
