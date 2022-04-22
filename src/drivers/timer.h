#pragma once

#include "../lib/asmfun.h"
#include <cstdint>

struct Timer {
    uint64_t count;
    uint8_t ms, s, m, h;
    uint64_t timeout; // 还剩多少时间
    uint8_t data;
};

static Timer timer_ctl;

uint64_t now();



void init_pit();
extern "C" {
    // 中断发生，先调用汇编中的中断处理程序，汇编再调用C函数
    extern void asm_response_pit();
    void response_pit();
}


