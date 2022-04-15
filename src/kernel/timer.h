#pragma once
#include "asmfun.h"

struct Timer {
    uint64_t count;
};

static Timer timer_ctl;

uint64_t now();
void init_pit();
extern "C" {
    // 中断发生，先调用汇编中的中断处理程序，汇编再调用C函数
    extern void asm_response_pit();
    void response_pit();
}


