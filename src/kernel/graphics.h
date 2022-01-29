#pragma once
#include "constants.h"

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

void fill_box(int x, int y, int w, int h, int color);
void draw_cursor(int x, int y);
