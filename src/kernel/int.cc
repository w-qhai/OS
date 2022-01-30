#include "int.h"

void response_keyboard() {
    out_byte(0x20, 0x61);       // 重新监听中断
    char c = in_byte(0x0060);   // 按键在0x0060端口
    fill_box(0, 0, 100, 16, 0);
    draw_number(c, 16, 0, 0, 15);
}

void response_mouse() {
    // out_byte(0xa0, 0x64); /* 通知PIC“IRQ-01已经受理完毕” */
    // out_byte(0x21, 0x62); /* 通知PIC“IRQ-01已经受理完毕” */
    // unsigned char data;
    // data = in_byte(0x0060);
    fill_box(0, 16, 100, 16, 0);
    draw_string("MOUSE", 0, 16, 15);
}

void response_int27() {
    out_byte(0x20, 0x67); /* 通知PIC的IRQ-07（参考7-1） */
}