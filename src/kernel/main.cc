#include "asmfun.h"
#include "fonts.h"
#include "graphics.h"
#include "int.h"
#include "queue.h"
#include "mouse.h"
#include "keyboard.h"
#include "memory.h"
#include "layer.h"

void init_system();

int main(void) {
    // init_system();

    // layer_back = LayerManager::alloc();
    // layer_back->set_buff(nullptr, ::scrn_w, ::scrn_h, -1);      // 设置图层缓冲区
    // LayerManager::slide(layer_back, 0, 0);                      // 图层在（0，0）位置
    // LayerManager::updown(layer_back, 0);                        // 图层z坐标

    // layer_mouse = LayerManager::alloc();
    // layer_mouse->set_buff(nullptr, 8, 8, -1);
    // LayerManager::slide(layer_mouse, mouse.x, mouse.y);
    // LayerManager::updown(layer_mouse, 1);


    // layers_ctl.refresh();
    
    draw_string("PianOS", 0, 0, 9);
    draw_string("HHHAH", 0, 16, 9);
    
    while(1) {
        // cli();
        // if (!keyboard_buff.empty()) {
        //     uint8_t data = keyboard_buff.front();
        //     keyboard_buff.pop();
        //     sti();
        // }
        // if (!mouse_buff.empty()) {
        //     int mouse_date_size = 3;
        //     static int8_t data[3];  // 有符号接收
        //     static int read_status;
        //     //舍弃刚开始0xfa
        //     if (is_mouse_init == false && mouse_buff.front() == 0xfa) {
        //         is_mouse_init = true;
        //         mouse_buff.pop();  
        //         read_status = 0;
        //         sti();
        //     } else if (is_mouse_init) { // 初始化完成
        //         data[read_status++] = mouse_buff.front();
        //         mouse_buff.pop();
        //         sti();
        //         if (read_status == mouse_date_size) { // 读完2字节
        //             mouse_decode(data);
        //             read_status = 0;
        //         } 
        //     }
        // }
        // sti(); 
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
