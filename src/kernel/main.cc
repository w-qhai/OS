#include "asmfun.h"
#include "fonts.h"
#include "graphics.h"
#include "int.h"
#include "queue.h"
#include "mouse.h"
#include "keyboard.h"
#include "memory.h"

#define Max_Layer   256
struct Layer {
    uint8_t* buff;
    int x, y;
    int width, height;
    int alpha;
    int z_index;
    int flags;

    void set_buff(uint8_t* buff, int width, int height, int alpha) {
        // this->buff = buff;
        MemoryManage::free(this->buff, this->width * this->height);
        this->buff = (uint8_t*)MemoryManage::alloc(width * height);
        this->width = width;
        this->height = height;
        this->alpha = alpha;
    }
};

class LayerControl {
public:
    uint8_t* vram;
    int width, height;
    int top;
    Layer* sheets[Max_Layer];
    Layer sheets0[Max_Layer];
public:
    LayerControl() {
        this->vram = ::vram;
        this->width = scrn_w;
        this->height = scrn_h;
        this->top = -1;
        for (int i = 0; i < Max_Layer; i++) {
            sheets0[i].flags = 0;   // 未被使用
        }
    }

    Layer* alloc() {
        Layer* layer = nullptr;
        for (int i = 0; i < Max_Layer; i++) {
            if (sheets0[i].flags == 0) {
                layer = sheets0 + i;
                layer->flags = 1;
                layer->z_index = -1;
                break;
            }
        }
        return layer;
    }

    void updown(Layer* layer, int z_index) {
        int old_z_index = layer->z_index;
        z_index = min(z_index, this->top + 1);
        z_index = max(z_index, -1);

        layer->z_index = z_index;

        if (old_z_index > z_index) { // 比以前低
            if (z_index >= 0) {
                for (int i = old_z_index; i > z_index; i--) {
                    sheets[i] = sheets[i-1];
                    sheets[i]->z_index = i;
                }
                sheets[z_index] = layer;
            }
            else {
                if (this->top > old_z_index) {
                    for (int i = old_z_index; i < this->top; i++) {
                        sheets[i] = sheets[i+1];
                        sheets[i]->z_index = i;
                    }
                }
                this->top--;
            }
        }        
        else if (old_z_index < z_index) { // 比以前低
            if (old_z_index >= 0) {
                for (int i = old_z_index; i < z_index; i++) {
                    sheets[i] = sheets[i+1];
                    sheets[i]->z_index = i;
                }
                sheets[z_index] = layer;
            }
            else {
                for (int i = this->top; i >= z_index; i--) {
                    sheets[i+1] = sheets[i];
                    sheets[i+1]->z_index = i + 1;
                }
                sheets[z_index] = layer;
                this->top++;
            }
        }
        refresh();
    }

    void refresh() {
        for (int i = 0; i < this->top; i++) {
            Layer* layer = sheets[i];
            for (int y = 0; y < layer->height; y++) {
                int ry = y + layer->y;
                for (int x = 0; x < layer->width; x++) {
                    int rx = x + layer->x;
                    if (layer->buff[y * layer->width + x] != layer->alpha) {
                        ::vram[ry * layer->width + rx] = layer->buff[y * layer->width + x];
                    }
                }
            }
        }
    }

    void slide(Layer* layer, int x, int y) {
        layer->x = x;
        layer->y = y;
        if (layer->z_index >= 0) {
            refresh();
        }
    }

    void free(Layer* layer) {
        if (layer->height >= 0) {
            updown(layer, -1);
        }
        layer->flags = 0;
    }
};

LayerControl layers_ctl;
Layer* layer_back;
Layer* layer_mouse;

void init_system();
void init_screen() {
    // static char s1[] = "PianOS";
    // draw_string(s1, 0, 0, 9);
}

int main(void) {
    init_system();

    layer_back = layers_ctl.alloc();
    layer_back->set_buff(nullptr, ::scrn_w, ::scrn_h, -1);  // 设置图层缓冲区
    layers_ctl.slide(layer_back, 0, 0);                     // 图层在（0，0）位置
    layers_ctl.updown(layer_back, 0);                       // 图层z坐标

    layer_mouse = layers_ctl.alloc();
    layer_mouse->set_buff(nullptr, 8, 8, -1);
    layers_ctl.slide(layer_mouse, mouse.x, mouse.y);
    layers_ctl.updown(layer_mouse, 1);


    layers_ctl.refresh();
    
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
    MemoryManage::init();
    int idt = get_idt();
    set_idt_seg((IDT_Descriptor*)idt + 0x21, (int)asm_response_keyboard, 8, 0x008e);
    set_idt_seg((IDT_Descriptor*)idt + 0x2c, (int)asm_response_mouse, 8, 0x008e);

    out_byte(0x21, 0b11111001); /* 开放PIC1和键盘中断(11111001) */
	out_byte(0xa1, 0b11101111); /* 开放鼠标中断(11101111) */

    init_keyboard();
    enable_mouse();
    is_mouse_init = false;

    MemoryManage::free((void*)0, MemoryManage::size);
    MemoryManage::alloc(final());
}
