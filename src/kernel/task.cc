#include "task.h"

TaskCtl task_ctl;

Task* task_init() {
    GDT_Descriptor* gdt = get_gdt();
    for (int i = 0; i < 2; i++) {
        task_ctl.pool[i].flags = 0;
        task_ctl.pool[i].selector = (TASK_GDT0 + i) * 8;
        set_gdt_seg(gdt + TASK_GDT0 + i, 103, (uint32_t)&(task_ctl.pool[i].tss), 0x0089);
    }

    // 当前执行的程序，已经变成一个任务了
    Task* task = task_alloc();
    task->flags = RUNING;    // 活动中标志
    task_ctl.runing_count = 1;
    task_ctl.now = 0;
    task_ctl.tasks[0] = task;
    load_tr(task->selector);
    task_ctl.timer.set_timeout(2);
    return task;
}

Task* task_alloc() {
    for (int i = 0; i < TASK_COUNT; i++) {
        if (task_ctl.pool[i].flags == 0) {
            task_ctl.pool[i].flags = 1;
            Task* task = &task_ctl.pool[i];
            task->tss.eflags= 0x00000202; // IF=1
            task->tss.eax   = 0;
            task->tss.ecx   = 0;
            task->tss.edx   = 0;
            task->tss.ebx   = 0;
            task->tss.ebp   = 0;
            task->tss.esi   = 0;
            task->tss.edi   = 0;
            task->tss.es    = 0;
            task->tss.ds    = 0;
            task->tss.fs    = 0;
            task->tss.gs    = 0;
            task->tss.ldtr  = 0;
            task->tss.iomap = 0x40000000;
            return task;
        }
    }
    return nullptr;
}

void task_run(Task* task) {
    task->flags = RUNING; /*活动中标志*/
    task_ctl.tasks[task_ctl.runing_count++] = task;
}

void task_switch() {
    // set_timeout(task, timer, 2);
    if (task_ctl.runing_count > 1) {
        task_ctl.now = (task_ctl.now + 1) % task_ctl.runing_count;
        switch_task(0, task_ctl.tasks[task_ctl.now]->selector);
    }
}