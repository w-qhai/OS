#include "asmfun.h"
#include "fonts.h"
#include "graphics.h"
#include "int.h"
#include "queue.h"
#include "mouse.h"
#include "keyboard.h"
#include "memory.h"

MemoryManage mem_manage;

void init_system();
void init_screen() {
    draw_cursor(mouse.x, mouse.y);
    static char s1[] = "PianOS";
    draw_string(s1, 2, scrn_h - 18, 12);
    draw_number(mem_size / 1024, 10, 10, 0, 0, 9); // 打印内存大小
    draw_number(final(), 10, 0, 0,  16, 9); // 系统大小
    int unused = (mem_size - final()) / 1024; 
    draw_number(unused, 10, 10, 0, 48, 9);  // 应该空闲大小
    draw_number(mem_manage.total() / 1024, 10, 10, 0, 64, 9);   // 实际空闲大小
}

int main(void) {
    init_system();
    init_screen();
    
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
                read_status = 0;
                sti();
            } else if (is_mouse_init) { // 初始化完成
                data[read_status++] = mouse_buff.front();
                mouse_buff.pop();
                sti();
                if (read_status == mouse_date_size) { // 读完2字节
                    mouse_decode(data);
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

    init_keyboard();
    enable_mouse();
    is_mouse_init = false;

    uint32_t ax = *(uint32_t*)(0x90002);
    uint32_t bx = *(uint32_t*)(0x90004);

    mem_size = (ax + bx); // 计算内存大小
    mem_manage.init();
    mem_manage.free((void*)0, mem_size);
    mem_manage.alloc(final());
}
