#include "int.h"

void response_keyboard() {
    char data = in_byte(0x0060);   // 按键在0x0060端口
    keyboard_buff.push(data);
    out_byte(0x20, 0x61);       // 重新监听中断
}

void response_mouse() {
    unsigned char data = in_byte(0x0060);
    mouse_buff.push(data);
    out_byte(0xa0, 0x64);
    out_byte(0x20, 0x62);
}
