#include "asmfun.h"
#include "fonts.h"
#include "graphics.h"
#include "int.h"
#include "queue.h"
#include "mouse.h"
#include "keyboard.h"
#include "memory.h"
#include "layer.h"
#include "window.h"

lm::Layer* layer_back;
lm::Layer* layer_mouse;

static char mouse_info[20];
static char mem_info[128];

void init_system();
void init_layer();

int main(void) {

    init_system();
    init_layer();

    Window* log_win = create_window(scrn_w-370, 20, 300, 150, "Log");
    log_win->show();
    static char str_buff[128];
    // 显示 分辨率信息
    sprintf(str_buff, "> VRAM:   0x%x", vram);
    draw_string(str_buff, 0, 0, White, log_win);
    sprintf(str_buff, "> WIDTH:  %d", scrn_w);
    draw_string(str_buff, 0, 16, White, log_win);
    sprintf(str_buff, "> HEIGHT: %d", scrn_h);
    draw_string(str_buff, 0, 32, White, log_win);
    
    // 显示内存使用情况
    sprintf(str_buff, "> Memory: %dMB, Used: %dKB", 
        mm::total()>>20, (mm::total()-mm::empty())>>10);
    draw_string(str_buff, 0, 48, White, log_win);

    Window* counter_win = create_window(20, 50, 200, 200, "Counter");
    counter_win->show();
    int count = 0;
    while(true) {
        cli();
        draw_string(count++, 0, 0, White, counter_win);
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
                read_status = 0;
                sti();
            } else if (is_mouse_init) { // 初始化完成
                data[read_status++] = mouse_buff.front();
                mouse_buff.pop();
                sti();
                if (read_status == mouse_date_size) { // 读完2字节
                    Mouse tm = mouse;
                    mouse_decode(data);
                    lm::slide(layer_mouse, mouse.x, mouse.y);  
                    sprintf(mouse_info, "> (%d, %d)      ", mouse.x, mouse.y);
                    draw_string(mouse_info, 0, 16*4, White, log_win);
                    read_status = 0;
                } 
            }
        }
        sti(); 
    }
    return 0;
}


void init_system() {
    mm::init();
    int idt = get_idt();
    set_idt_seg((IDT_Descriptor*)idt + 0x21, (int)asm_response_keyboard, 8, 0x008e);
    set_idt_seg((IDT_Descriptor*)idt + 0x2c, (int)asm_response_mouse, 8, 0x008e);

    out_byte(0x21, 0b11111001); /* 开放PIC1和键盘中断(11111001) */
	out_byte(0xa1, 0b11101111); /* 开放鼠标中断(11101111) */

    init_keyboard();
    enable_mouse();
    is_mouse_init = false;

    scrn_w = *(uint16_t*)(0x90020);
    scrn_h = *(uint16_t*)(0x90022);
    vram = (uint8_t*)(*(uint32_t*)(0x90024));
}

void init_layer() {
//==============桌面层==============
    layer_back = lm::alloc(
        (uint8_t*) mm::alloc(scrn_w*scrn_h), // 直接申请内存
        scrn_w, scrn_h, -1);  // 设置图层缓冲区

    lm::slide(layer_back, 0, 0);                      // 图层在（0，0）位置
    lm::updown(layer_back, 0);
    draw_desktop(layer_back);

//==============鼠标层==============
    layer_mouse = lm::alloc(
        (uint8_t*)mm::alloc(curosr_size*curosr_size), 
        curosr_size, curosr_size, 99);

    lm::slide(layer_mouse, mouse.x, mouse.y);
    lm::updown(layer_mouse, 1);
    draw_cursor(0, 0, layer_mouse);
}