#include "asmfun.h"
#include "fonts.h"
#include "graphics.h"
#include "int.h"
#include "queue.h"
#include "mouse.h"
#include "keyboard.h"
#include "memory.h"
#include "layer.h"

static char mouse_info[20];
uint8_t buff_back[win_w * win_h] = { 0 };
uint8_t buff_mouse[curosr_size * curosr_size] = { 0 };

Layer* layer_back;
Layer* layer_mouse;

void init_system();
void init_layer() {
//==============桌面层==============
    layer_back = LayerManager::alloc(buff_back, ::scrn_w, ::scrn_h, -1);  // 设置图层缓冲区
    LayerManager::slide(layer_back, 0, 0);                      // 图层在（0，0）位置
    LayerManager::updown(layer_back, 0);
    draw_desktop(layer_back);
    
//==============鼠标层==============
    layer_mouse = LayerManager::alloc(buff_mouse, curosr_size, curosr_size, 99);
    LayerManager::slide(layer_mouse, mouse.x, mouse.y);
    LayerManager::updown(layer_mouse, 1);
    draw_cursor(0, 0, layer_mouse);

}
int main(void) {
    init_system();
    init_layer();

    while(true) {
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
                read_status = 0;
                sti();
            } else if (is_mouse_init) { // 初始化完成
                data[read_status++] = mouse_buff.front();
                mouse_buff.pop();
                sti();
                if (read_status == mouse_date_size) { // 读完2字节
                    Mouse tm = mouse;
                    mouse_decode(data);
                    LayerManager::slide(layer_mouse, mouse.x, mouse.y);  
                    sprintf(mouse_info, "(%d, %d)", mouse.x, mouse.y);
                    draw_string(mouse_info, 0, 0, 10, layer_back);
                    read_status = 0;
                } 
            }
        }
        sti(); 
    }
    return 0;
}


void init_system() {
    MemoryManager::init();
    int idt = get_idt();
    set_idt_seg((IDT_Descriptor*)idt + 0x21, (int)asm_response_keyboard, 8, 0x008e);
    set_idt_seg((IDT_Descriptor*)idt + 0x2c, (int)asm_response_mouse, 8, 0x008e);

    out_byte(0x21, 0b11111001); /* 开放PIC1和键盘中断(11111001) */
	out_byte(0xa1, 0b11101111); /* 开放鼠标中断(11101111) */

    init_keyboard();
    enable_mouse();
    is_mouse_init = false;

    MemoryManager::free((void*)0, MemoryManager::size);
    MemoryManager::alloc(final());
}
