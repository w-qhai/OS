#include "timer.h"

void init_pit() {
    // 中断周期0x2e9c=11932,频率100Hz,10ms发生一次中断
    out_byte(0x43, 0x34);   //
    out_byte(0x40, 0x9c);   // 0x9c中断周期的低8位
    out_byte(0x40, 0x2e);   // 0x2e中断周期的高8位
    timer_ctl.count = 0;
}

void response_pit() {
    out_byte(0x20, 0x60);
    timer_ctl.count++;
}

uint64_t now() {
    return timer_ctl.count;
}