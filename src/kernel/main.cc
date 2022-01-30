#include "asmfun.h"
#include "fonts.h"
#include "graphics.h"
#include "int.h"

void draw_desktop();

#define PORT_KEYDAT             0x0060
#define PORT_KEYSTA             0x0064
#define PORT_KEYCMD             0x0064
#define KEYSTA_SEND_NOTREADY    0x02
#define KEYCMD_WRITE_MODE       0x60
#define KBC_MODE                0x47

void wait_KBC_sendready(void) {
	while (1) {
		if ((in_byte(PORT_KEYSTA) & KEYSTA_SEND_NOTREADY) == 0) {
			 break;
		}
	}
}

void init_keyboard(void) {
	wait_KBC_sendready();
	out_byte(PORT_KEYCMD, KEYCMD_WRITE_MODE);
	wait_KBC_sendready();
	out_byte(PORT_KEYDAT, KBC_MODE);
}

#define KEYCMD_SENDTO_MOUSE		0xd4
#define MOUSECMD_ENABLE			0xf4

void enable_mouse(void) {
	wait_KBC_sendready();
	out_byte(PORT_KEYCMD, KEYCMD_SENDTO_MOUSE);
	wait_KBC_sendready();
	out_byte(PORT_KEYDAT, MOUSECMD_ENABLE);
}


int main(void) {
    sti();
    out_byte(0x21, 0b11111001); /* 开放PIC1和键盘中断(11111001) */
	out_byte(0xa1, 0b11101111); /* 开放鼠标中断(11101111) */
    
    init_keyboard();
    // enable_mouse();

    draw_cursor(120, 100);
    static char s1[] = "PianOS";
    draw_string(s1, 2, scrn_h - 18, 12);

    int idt = get_idt();
    set_idt_seg((IDT_Descriptor*)idt + 0x21, (int)asm_response_keyboard, 8, 0x008e);
    set_idt_seg((IDT_Descriptor*)idt + 0x27, (int)asm_response_int27, 2 * 8, 0x008e);
    // set_idt_seg((IDT_Descriptor*)idt + 0x2c, (int)asm_response_mouse, 8, 0x008e);
    
    while(1);
    
    return 0;
}

void draw_desktop() {
    fill_box(0, 0, scrn_w, scrn_h, 0x0f);
    int white_count = 7;
    int white_width = scrn_w / white_count;
    for (int i = 1; i < white_count; i++) {
        fill_box(i * white_width, 0, 1, scrn_h, 0);
    }

    int black_width = white_width * 2 / 3;
    for (int i = 1; i < white_count; i++) {
        if ((i + 1) % 4 == 0) {
            continue;
        }
        fill_box(i * white_width - black_width / 2, 0, black_width, scrn_h * 2 / 3, 0);
    }

    fill_box(0, scrn_h - 21, scrn_w, 1, 5);
    fill_box(0, scrn_h - 20, scrn_w, 20, 7);
}
