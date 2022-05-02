#include "../lib/asmfun.h"
#include "../lib/list.hpp"

#include "../drivers/timer.h"
#include "../drivers/mouse.h"
#include "../drivers/keyboard.h"

#include "../graphics/fonts.h"
#include "../graphics/graphics.h"
#include "../graphics/layer.h"
#include "../graphics/window.h"

#include "../mm/memory.h"

#include "task.h"

TSS32 tss_a, tss_b;

lm::Layer* layer_back;
lm::Layer* layer_mouse;

static char str_buff[128];

void init_system();
void init_layer();

uint8_t handle_keyboard();
uint8_t handle_mouse();

int sel_win_id = -1;
// 任务b处理鼠标事件
// 主任务处理键盘事件
void task_b_main() {
    // tm::Timer timer;
    // timer.set_timeout(2);
    // timer.start();
    Window* mul_task_win = create_window(150, 150, 300, 100, "MulTask");
    mul_task_win->show();
    while (true) {
        cli();
        tm::Time now = tm::now();
        sprintf(str_buff, "%02d:%02d:%02d:%02d", now.h, now.m, now.s, now.ms);
        draw_string(str_buff, 0, 0, Black, mul_task_win);
        if (handle_mouse()) {
            sprintf(str_buff, "(%d, %d) ", mouse.x, mouse.y);
            draw_string(str_buff, 0, 16*2, Black, mul_task_win);
            //  左键按下
            if (mouse.button & 0x01) {
                Window* win = sel_win_id>=0 ? Window::windows[sel_win_id] : nullptr;
                if (win != nullptr) { // 窗口存在
                    int dx = mouse.x - win->x;
                    int dy = mouse.y - win->y;
                    if (mouse.x > win->x && mouse.x < win->x + win->width &&
                        mouse.y > win->y && mouse.y < win->y + win->height ) {
                        win->move(mouse.x - win->width/2, mouse.y-win->height/2);
                    }
                }
            }
        }
        sti();
    }
}

int main(void) {

    init_system();
    init_layer();

    Window* log_win = create_window(scrn_w-370, 20, 300, 150, "Log");
    log_win->show();

    Window* timer_win = create_window(20, 50, 130, 50, "Timer");
    timer_win->show();

    Window* input_win = create_window(280, 300, 200, 50, "Input");
    input_win->show();

    /*======多任务代码=======*/
    tss_a.ldtr = 0;
    tss_a.iomap = 0x40000000;
    int task_b_esp = (int)mm::alloc(64*1024)+64*1024; // 64K栈大小，
    tss_b.ldtr  = 0;
    tss_b.iomap = 0x40000000;
    tss_b.eip   = (int)&task_b_main;
    tss_b.eflags = 0x00000202; // IF=1
    tss_b.eax   = 0;
    tss_b.ecx   = 0;
    tss_b.edx   = 0;
    tss_b.ebx   = 0;
    tss_b.esp   = task_b_esp;
    tss_b.ebp   = 0;
    tss_b.esi   = 0;
    tss_b.edi   = 0;
    tss_b.es    = 2 * 8;
    tss_b.cs    = 1 * 8;    // 当前代码段1
    tss_b.ss    = 2 * 8;    // 栈段必须在2
    tss_b.ds    = 2 * 8;
    tss_b.fs    = 2 * 8;
    tss_b.gs    = 2 * 8;

    task_init();
    Task* task_b = task_alloc();
    task_b->tss = tss_b;
    task_run(task_b);

    // tm::Timer timer;
    // timer.set_timeout(2);
    // timer.start();

    // 显示 分辨率信息
    /*======================*/
    while(true) {
        cli();
        // 计时器
        tm::Time now = tm::now();
        sprintf(str_buff, "%02d:%02d:%02d:%02d", now.h, now.m, now.s, now.ms);
        draw_string(str_buff, 0, 0, Black, timer_win);

        // 每20ms切换任务
        // if (timer.timeout()) {
        //     switch_task(0, 4*8);
        // }

        uint8_t data = handle_keyboard();
        static int cursor_x = 0;
        static int cursor_y = 0;

        // 处理键盘按键
        if (data != 0 && data < 0x54) {
            // 打印码
            sprintf(str_buff, "$ INPUT: %d", data);
            draw_string(str_buff, 0, 16*5, Black, log_win);
            switch (data)
            {
            case 14:    // backspace
                if (cursor_x > 0) {
                    draw_string(" ", cursor_x, cursor_y, Black, input_win);
                    draw_string("_", cursor_x -= 8, cursor_y, Black, input_win);
                }
                break;
            case 15:
                Window::windows[sel_win_id]->deactivate();
                sel_win_id++;
                if (sel_win_id == Window::count) {
                    sel_win_id = -1;
                }
                else {
                    Window::windows[sel_win_id]->activate();
                }
                break;
            case 28:    // enter
                break;
            default:    // 可见字符
                if (key_table[data]) {
                    if (cursor_x+8*3 < input_win->width) {
                        sprintf(str_buff, "%c", key_table[data]);
                        draw_string(str_buff, cursor_x, cursor_y, Black, input_win);
                        cursor_x += 8;
                    }
                }
                break;
            }
        }

        // 光标闪烁
        static int counter=0;
        static tm::Timer timer1;
        timer1.set_timeout(10);
        timer1.start();
        if (timer1.timeout()) {
            counter = !counter;
            if (counter) {
                draw_string(" ", cursor_x, cursor_y, Black, input_win);
            }
            else {
                draw_string("_", cursor_x, cursor_y, Black, input_win);
            }
        }
        // 显示内存使用情况
        static int total = 0;
        if (total != mm::total()) {
            sprintf(str_buff, "$ Memory: %dMB, Used: %dKB", 
                mm::total()>>20, (mm::total()-mm::empty())>>10);
            draw_string(str_buff, 0, 48, Black, log_win);
            total = mm::total();
        }
        sti(); 
    }
    return 0;
}


void init_system() {
    mm::init(); // 内存管理初始化
    IDT_Descriptor* idt = get_idt();
    set_idt_seg(idt + 0x20, (int)asm_response_pit, 8, 0x008e);
    set_idt_seg(idt + 0x21, (int)asm_response_keyboard, 8, 0x008e);
    set_idt_seg(idt + 0x2c, (int)asm_response_mouse, 8, 0x008e);

    out_byte(0x21, 0b11111000); /* PIT,开放PIC1和键盘中断(11111000) */
	out_byte(0xa1, 0b11101111); /* 开放鼠标中断(11101111) */

    init_keyboard();
    enable_mouse();
    init_pit(); // 定时器
    sti();
    is_mouse_init = false;

    scrn_w = *(uint16_t*)(0x90020);
    scrn_h = *(uint16_t*)(0x90022);
    vram = (uint8_t*)(*(uint32_t*)(0x90024));

    lm::init(scrn_w, scrn_h);

    // task_init();
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
    mouse.x = scrn_w / 2;
    mouse.y = scrn_h / 2;
    layer_mouse = lm::alloc(
        (uint8_t*)mm::alloc(curosr_size*curosr_size), 
        curosr_size, curosr_size, 99);

    lm::slide(layer_mouse, mouse.x, mouse.y);
    lm::updown(layer_mouse, 1);
    draw_cursor(0, 0, layer_mouse);

}

uint8_t handle_keyboard() {
    if (!keyboard_buff.empty()) {
        uint8_t data = keyboard_buff.front();
        keyboard_buff.pop();
        return data;
    }
    return 0;
}

uint8_t handle_mouse() {
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
                read_status = 0;
                return 1;
            } 
        }
    }
    return 0;
}