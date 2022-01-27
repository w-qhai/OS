#pragma once
#include <stdint.h>

/**
 * @brief 颜色代码
 * 0 黑
 * 1 蓝
 * 2 绿
 * 3 暗蓝
 * 4 红
 * 5 紫
 * 6 暗黄
 * 7 浅灰
 * 8 深灰
 * 9 浅亮蓝
 * a 亮绿
 * b 亮蓝
 * c 亮红
 * d 亮紫
 * e 黄
 * f 白色
 */

void mem_set(int addr, int bytes, int data);

void cli();
void sti();
void io_set_flags(int flags);
int io_get_flags();

// in  al/ax/eax port
int in_byte(int port);
int in_word(int port);
int in_dword(int port);

// out port data
void out_byte(int port, int data);
void out_word(int port, int data);
void out_dword(int port, int data);

// 测试内联汇编
void movb(int addr, int data);