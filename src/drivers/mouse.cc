#include "mouse.h"
Mouse mouse;
CirQueue<uint8_t, MOUSE_BUFF_SIZE> mouse_buff;
bool is_mouse_init = false;
void enable_mouse() {
    while (in_byte(0x64) & 0x02);
	out_byte(0x64, 0xd4);
	while (in_byte(0x64) & 0x02);
	out_byte(0x60, 0xf4);
}

void response_mouse() {
    uint8_t data = in_byte(0x0060);
    mouse_buff.push(data);
    out_byte(0xa0, 0x64);
    out_byte(0x20, 0x62);
}


void mouse_decode(const int8_t data[]) {
    mouse.button = data[0] & 0x07;  // 取后三位

    mouse.x += data[1];
    mouse.y -= data[2];

    mouse.x = max(mouse.x, 0);
    mouse.y = max(mouse.y, 0);

    mouse.x = min(mouse.x, scrn_w - 1);
    mouse.y = min(mouse.y, scrn_h - 1);
}