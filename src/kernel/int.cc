#include "int.h"

extern Queue keyboard_buff;
// extern Queue keyboard_buff;
void init_keyboard_mouse(void) {
	while (in_byte(0x64) & 0x02);
	out_byte(0x64, 0x60);
	while (in_byte(0x64) & 0x02);
	out_byte(0x60, 0x47);
    while (in_byte(0x64) & 0x02);
	out_byte(0x64, 0xd4);
	while (in_byte(0x64) & 0x02);
	out_byte(0x60, 0xf4);
}


void response_keyboard() {
    char data = in_byte(0x0060);   // 按键在0x0060端口
    keyboard_buff.push(data);
    out_byte(0x20, 0x61);       // 重新监听中断
}

static int read_status = 0, mouse_init = false;
static char mdata[3];
void response_mouse() {
    unsigned char data = in_byte(0x0060);
    mouse_buff.push(data);
    out_byte(0xa0, 0x64);
    out_byte(0x20, 0x62);
}
