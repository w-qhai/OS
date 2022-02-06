#include "keyboard.h"

void init_keyboard(void) {
	while (in_byte(0x64) & 0x02);
	out_byte(0x64, 0x60);
	while (in_byte(0x64) & 0x02);
	out_byte(0x60, 0x47);
}