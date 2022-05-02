#pragma once

#include "../lib/constants.h"
#include "../lib/list.hpp"
#include "../lib/asmfun.h"
#include "../mm/memory.h"
#include "../drivers/timer.h"
#include <cstdint>

#define TASK_GDT0 3 //GDT从3号开始分配TSS
#define RUNING 2

struct TSS32 {
    uint32_t backlink, esp0, ss0, esp1, ss1, esp2, ss2, cr3;
	uint32_t eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
	uint32_t es, cs, ss, ds, fs, gs;
	uint32_t ldtr=0, iomap=0x40000000;
};

struct Task {
    uint32_t selector, flags;
    TSS32 tss;
};


#define TASK_COUNT 128  // 236会出bug，无法使用键盘
struct TaskCtl {
    int runing_count; // 正在运行的任务数量
    int now; // 用来记录当前正在运行的任务
    Task* tasks[TASK_COUNT];
    Task  pool[TASK_COUNT];
    tm::Timer timer;
};

extern TaskCtl task_ctl;

Task* task_init();
Task* task_alloc();
void task_run(Task* task);
void task_switch();