#include "timer.h"
#include "../kernel/task.h"

uint32_t tm::count;
Queue<uint32_t, MAX_TIMER> tm::timer_info;

void init_pit() {
    // 中断周期0x2e9c=11932,频率100Hz,10ms发生一次中断
    out_byte(0x43, 0x34);   //
    out_byte(0x40, 0x9c);   // 0x9c中断周期的低8位
    out_byte(0x40, 0x2e);   // 0x2e中断周期的高8位
    tm::count = 0;
}

void tm::Timer::start() {
    if (!runing) {
        runing = true;
        _start = count;
    }
}

void tm::Timer::set_timeout(uint32_t timeout) {
    _timeout = timeout;
    // _start = count;
}

bool tm::Timer::timeout() {
    // if (runing && (count-_start) == _timeout) {
    //     return true;
    // }
    if (runing && (count-_start) % _timeout == 0) {
        return true;
    }
    return false;
}

tm::Time tm::now() {
    Time time;
    uint32_t ss = count / 100;
    time.h = ss / 3600;
    time.m = ss % 3600 / 60;
    time.s = ss % 60;
    time.ms = count % 100;
    return time;
}

void response_pit() {
    out_byte(0x20, 0x60);
    tm::count++;
    // if (task_ctl.timer.timeout()) {
    //     task_switch();
    // }
    if (tm::count % 2 == 0) {
        task_switch();
    }
}