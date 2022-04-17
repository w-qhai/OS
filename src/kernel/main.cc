#include "asmfun.h"
#include "fonts.h"
#include "graphics.h"
#include "queue.h"
#include "mouse.h"
#include "keyboard.h"
#include "memory.h"
#include "layer.h"
#include "window.h"
#include "timer.h"

struct TSS32 {
    uint32_t backlink, esp0, ss0, esp1, ss1, esp2, ss2, cr3;
	uint32_t eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
	uint32_t es, cs, ss, ds, fs, gs;
	uint32_t ldtr, iomap;
};

TSS32 tss_a, tss_b;


lm::Layer* layer_back;
lm::Layer* layer_mouse;

static char mouse_info[20];
static char mem_info[128];
static char str_buff[128];

void init_system();
void init_layer();

uint8_t handle_keyboard();
uint8_t handle_mouse();

void task_b_main() {
    while (1) {
        
    }
}

int main(void) {

    init_system();
    init_layer();

    Window* log_win = create_window(scrn_w-370, 20, 300, 150, "Log");
    log_win->show();
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

    Window* timer_win = create_window(20, 50, 130, 50, "Timer");
    timer_win->show();

    Window* input_win = create_window(280, 220, 200, 50, "Input");
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
    tss_b.cs    = 1 * 8;
    tss_b.ss    = 2 * 8;
    tss_b.ds    = 2 * 8;
    tss_b.fs    = 2 * 8;
    tss_b.gs    = 2 * 8;

    GDT_Descriptor* gdt = get_gdt();
    set_gdt_seg(gdt+3, 103, (int)&tss_a, 0x0089);
    set_gdt_seg(gdt+4, 103, (int)&tss_b, 0x0089);


    load_tr(3*8);

    /*======================*/
    while(true) {
        cli();
        // 计时器
        int h, m, s, ms, t = now();
        ms = t % 100;
        t /= 100;
        h = t / 3600;
        m = t % 3600 / 60;
        s = t % 60;
        sprintf(str_buff, "%02d:%02d:%02d:%02d", h, m, s, ms);
        draw_string(str_buff, 0, 0, White, timer_win);

        if(s && s % 2 == 0) {
            switch_task(0, 4*8);
        }

        uint8_t data = handle_keyboard();
        static int cursor_x = 0;
        static int cursor_y = 0;
        if (data != 0 && data < 0x54) {
            // 打印码
            sprintf(str_buff, "%d", data);
            draw_string(str_buff, 0, 16*6, White, input_win);
            switch (data)
            {
            case 14:    // backspace
                if (cursor_x > 0) {
                    draw_string(" ", cursor_x, cursor_y, White, input_win);
                    draw_string("_", cursor_x -= 8, cursor_y, White, input_win);
                }
                break;
            case 28:    // enter
                break;
            default:    // 可见字符
                if (key_table[data]) {
                    sprintf(str_buff, "%c", key_table[data]);
                    draw_string(str_buff, cursor_x, cursor_y, White, input_win);
                    draw_string("_", cursor_x += 8, cursor_y, White, input_win);
                }
                break;
            }
        }

        if (handle_mouse()) {
            sprintf(mouse_info, "> (%d, %d)      ", mouse.x, mouse.y);
            draw_string(mouse_info, 0, 16*4, White, log_win);
            if (mouse.button & 0x01) {
                input_win->move(mouse.x, mouse.y);
            }
        }
        sti(); 
    }
    return 0;
}


void init_system() {
    mm::init();
    IDT_Descriptor* idt = get_idt();
    set_idt_seg(idt + 0x20, (int)asm_response_pit, 8, 0x008e);
    set_idt_seg(idt + 0x21, (int)asm_response_keyboard, 8, 0x008e);
    set_idt_seg(idt + 0x2c, (int)asm_response_mouse, 8, 0x008e);

    out_byte(0x21, 0b11111000); /* PIT,开放PIC1和键盘中断(11111000) */
	out_byte(0xa1, 0b11101111); /* 开放鼠标中断(11101111) */

    init_keyboard();
    enable_mouse();
    init_pit(); // 定时器
    is_mouse_init = false;

    scrn_w = *(uint16_t*)(0x90020);
    scrn_h = *(uint16_t*)(0x90022);
    vram = (uint8_t*)(*(uint32_t*)(0x90024));

    lm::init(scrn_w, scrn_h);
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

uint8_t handle_keyboard() {
    if (!keyboard_buff.empty()) {
        uint8_t data = keyboard_buff.front();
        keyboard_buff.pop();
        sti();
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