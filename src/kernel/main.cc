#include "asmfun.h"
#include "fonts.h"

// #include <string>

// 显存 0xa0000~0xaffff
char* const vram = (char*)0xa0000;
char* const init_addr = (char*)0x90000;
const int scrn_w = 320;
const int scrn_h = 200;
const int g_size = 0xffff;
const int t_vram = 0xb8000;

struct InitInfo {
    uint8_t cursor_x;
    uint8_t cursor_y;
    uint8_t mem_size;
    uint8_t reserved1;
    uint8_t display_page;
    uint8_t video_mode;
    uint8_t scrn_w;
} init_info;

struct Point {
    int x;
    int y;
};

void fill_box(int x1, int y1, int x2, int y2, int color);
void draw_char(char c, int x, int y, int color);
void draw_string(char* str, int x, int y, int color);

// char* str = "PianOS";
int main(void) {

    fill_box(0, 0, scrn_w, scrn_h, 3);
    fill_box(0, scrn_h - 21, scrn_w, scrn_h - 20, 15);
    fill_box(0, scrn_h - 20, scrn_w, scrn_h, 7);

    draw_char(0, 10, 10, 0);
    draw_string("PianOS", 10, 26, 5);
    while(1);
    
    return 0;
}

void fill_box(int x1, int y1, int x2, int y2, int color) {
    if (x1 > x2 || y1 > y2) {
        return;
    }
    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {
            vram[j * scrn_w + i] = color;
        }
    }
}

void draw_char(char c, int x, int y, int color) {
    // 字体 16 * 8
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 8; j++) {
            if (fonts[c][i] & (0x80 >> j)) {
                vram[(y + i)* scrn_w + x + j] = color;
            }
        }
    }
}

void draw_string(char* str, int x, int y, int color) {
    for (int i = 0; str[i]; i++) {
        draw_char(str[i], x + i * 9, y, color);
    }
}