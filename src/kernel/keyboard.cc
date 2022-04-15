#include "keyboard.h"

void init_keyboard(void) {
	while (in_byte(0x64) & 0x02);
	out_byte(0x64, 0x60);
	while (in_byte(0x64) & 0x02);
	out_byte(0x60, 0x47);
}

void response_keyboard() {
    char data = in_byte(0x0060);   // 按键在0x0060端口
    keyboard_buff.push(data);
    out_byte(0x20, 0x61);       // 重新监听中断
}