#include "keyboard.h"
Queue<uint8_t, KEYBOARD_BUFF_SIZE> keyboard_buff;

char key_table[0x54] = {
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '^', 0, 0,
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '@', '[', 0, 0, 'A', 'S',
	'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', ':', 0, 0, ']', 'Z', 'X', 'C', 'V',
	'B', 'N', 'M', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1',
	'2', '3', '0', '.'
};

void init_keyboard(void) {
	while (in_byte(0x64) & 0x02);
	out_byte(0x64, 0x60);
	while (in_byte(0x64) & 0x02);
	out_byte(0x60, 0x47);
}

void response_keyboard() {
    uint8_t data = in_byte(0x0060);   // 按键在0x0060端口
    keyboard_buff.push(data);
    out_byte(0x20, 0x61);       // 重新监听中断
}