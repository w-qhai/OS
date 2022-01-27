#include "graphics.h"

void fill_box(int x, int y, int w, int h, int color) {
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {
            vram[j * scrn_w + i] = color;
        }
    }
}

/**
 * @brief 
 * 
 * 000000000000000
 * 000000000000000
 * 000000000000000
 * 000000000000000
 * 000000000000000
 * 000000000000000
 * 000000000000000
 * 000000000000000
 * 000000000000000
 * 000000000000000
 * 000000000000000
 * 000000000000000
 * 000000000000000
 * 000000000000000
 */

void draw_cursor(int x, int y) {
    static uint8_t curosr[8] = {
        0b11111100,
        0b11111000,
        0b11110000,
        0b11111000,
        0b11001100,
        0b10000110,
        0b00000011,
        0b00000001
    };

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (curosr[i] & (0x80 >> j)) {
                vram[(y + i)* scrn_w + x + j] = 10;
            }
        }
    }
}
