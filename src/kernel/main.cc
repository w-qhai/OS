#include "asmfun.h"
#include "fonts.h"
#include "graphics.h"
#include "int.h"
#include "queue.h"

void draw_desktop();

void init_system();

struct Mouse {
    int button;
    int x, y;
} mouse = {0, 150, 50};
bool is_mouse_init = false; 


int main(void) {
    cli();
    init_system();
    draw_desktop();
    draw_cursor(mouse.x, mouse.y);
    static char s1[] = "PianOS";
    draw_string(s1, 2, scrn_h - 18, 12);
    
    sti();
    while(1) {
        cli();
        if (!keyboard_buff.empty()) {
            uint8_t data = keyboard_buff.front();
            keyboard_buff.pop();
            sti();
        }

        if (!mouse_buff.empty()) {
            int mouse_date_size = 3;
            static int8_t data[3];  // 有符号接收
            static int read_status;
            //舍弃刚开始0xfa
            if (is_mouse_init == false && mouse_buff.front() == 0xfa) {
                is_mouse_init = true;
                mouse_buff.pop();  
                draw_string("mouse inited", 100, 100, 9);
                read_status = 0;
                sti();
            } else if (is_mouse_init) { // 初始化完成
                data[read_status++] = mouse_buff.front();
                mouse_buff.pop();
                sti();
                if (read_status == mouse_date_size) { // 读完2字节
                    //------------ 绘制鼠标
                    fill_box(mouse.x, mouse.y, 8, 8, 0);
                    mouse.x += data[1];
                    mouse.y -= data[2];

                    mouse.x = max(mouse.x, 0);
                    mouse.y = max(mouse.y, 0);

                    mouse.x = min(mouse.x, scrn_w - 8);
                    mouse.y = min(mouse.y, scrn_h - 8);

                    draw_cursor(mouse.x, mouse.y);
                    //---------- 鼠标绘制结束
                    read_status = 0;
                } 
            }
        }
        sti(); 
    }
    return 0;
}


void init_system() {
    int idt = get_idt();
    set_idt_seg((IDT_Descriptor*)idt + 0x21, (int)asm_response_keyboard, 8, 0x008e);
    set_idt_seg((IDT_Descriptor*)idt + 0x2c, (int)asm_response_mouse, 8, 0x008e);

    out_byte(0x21, 0b11111001); /* 开放PIC1和键盘中断(11111001) */
	out_byte(0xa1, 0b11101111); /* 开放鼠标中断(11101111) */

    init_keyboard_mouse();
    is_mouse_init = false;
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
