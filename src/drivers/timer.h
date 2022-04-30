#pragma once

#include "../lib/asmfun.h"
#include "../lib/queue.hpp"
#include <cstdint>
#include <climits>

#define MAX_TIMER 500
extern "C" {
    // 中断发生，先调用汇编中的中断处理程序，汇编再调用C函数
    extern void asm_response_pit();
    void response_pit();
}

void init_pit();

namespace tm {
    extern uint32_t count;
    extern Queue<uint32_t, MAX_TIMER> timer_info;
    struct Time {
        uint8_t h;
        uint8_t m;
        uint8_t s;
        uint8_t ms;
    };
    struct Timer {
        bool runing = false;
        uint32_t _start = 0;
        uint32_t _timeout = 0;
        void start();
        void set_timeout(uint32_t timeout);
        bool timeout();
    };
    Time now();
}
