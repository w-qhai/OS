#include "asmfun.h"
#include "fonts.h"
#include "graphics.h"

void draw_desktop();

void fcun () {
    fill_box(200, 50, 8 * 30, 16, 0);
    draw_string("KeyBoard", 200 + 8 * 30, 50, 15);
    while (1);
}

int main(void) {
    sti();

    out_byte(0x21, 0b11111001); /* 开放PIC1和键盘中断(11111001) */
	// out_byte(0x21, 0b11101111); /* 开放鼠标中断(11101111) */


    // draw_desktop();
    draw_cursor(120, 100);
    draw_string("PianOS", 2, scrn_h - 18, 12);

    int idt = get_idt();
    set_idt_seg((IDT_Descriptor*)idt + 0x21, (int)(void*)fcun, 2 << 3, 0x008e);

    draw_number((int)(void*)fcun, 16, 300, 70, 15);

    int x = 300;
    int y = 100;
    while (idt) {
        draw_char(idt % 10 + '0', x, y, 6);
        idt /= 10;
        x -= 8;
    }
    
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
