#include "graphics.h"

void fill_box(int x, int y, int w, int h, int color) {
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {
            vram[j * scrn_w + i] = color;
        }
    }
}

void draw_cursor(int x, int y) {
    static uint8_t curosr[8] = {
        0b11111110,
        0b11111000,
        0b11110000,
        0b11111000,
        0b11011100,
        0b10001110,
        0b10000111,
        0b00000011
    };

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (curosr[i] & (0x80 >> j)) {
                vram[(y + i)* scrn_w + x + j] = 10;
            }
        }
    }
}
