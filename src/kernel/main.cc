#include "asmfun.h"
#include "fonts.h"
#include "graphics.h"
#include "int.h"

void draw_desktop();

void init_system();

int main(void) {
    int idt = get_idt();
    set_idt_seg((IDT_Descriptor*)idt + 0x21, (int)asm_response_keyboard, 8, 0x008e);
    set_idt_seg((IDT_Descriptor*)idt + 0x2c, (int)asm_response_mouse, 8, 0x008e);

    sti();
    out_byte(0x21, 0b11111001); /* 开放PIC1和键盘中断(11111001) */
	out_byte(0xa1, 0b11101111); /* 开放鼠标中断(11101111) */

    init_keyboard_mouse();
    init_system();
    draw_cursor(150, 50);
    static char s1[] = "PianOS";
    draw_string(s1, 2, scrn_h - 18, 12);
    
    while(1);
    
    return 0;
}

void init_system() {

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
