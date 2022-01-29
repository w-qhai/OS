#include "asmfun.h"
#include "fonts.h"
#include "graphics.h"

extern "C" {
    extern void asm_response_keyboard();
    void reponse_keyboard () {
        static bool visable = true;
        out_byte(0x20, 0x61);
        if (visable) {
            draw_string("KeyBoard", 200 + 8 * 30, 50, 15);
        }
        else {
            draw_string("        ", 200 + 8 * 30, 50, 15);
        }
        visable = !visable;
        char c = in_byte(0x0060);
        // fill_box(0, 0, 100, 16, 0);
        draw_number(c, 10, 0, 0, 15);
    }
}

void draw_desktop();

int main(void) {
    sti();

    out_byte(0x21, 0b11111001); /* 开放PIC1和键盘中断(11111001) */
	// out_byte(0x21, 0b11101111); /* 开放鼠标中断(11101111) */


    // draw_desktop();
    draw_cursor(120, 100);
    draw_string("PianOS", 2, scrn_h - 18, 12);

    int idt = get_idt();
    set_idt_seg((IDT_Descriptor*)idt + 0x21, (int)asm_response_keyboard, 8, 0x008e);

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
