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

void draw_desktop() {
    fill_box(0, 0, scrn_w, scrn_h, 0x0f);
    int white_count = 7;
    int white_width = scrn_w / white_count;
    for (int i = 1; i < white_count; i++) {
        fill_box(i * white_width, 0, 1, scrn_h, 0);
    }

    int black_width = white_width * 2 / 3;
    for (int i = 1; i < white_count; i++) {
        if ((i + 1) % 4 == 0) {
            continue;
        }
        fill_box(i * white_width - black_width / 2, 0, black_width, scrn_h * 2 / 3, 0);
    }

    fill_box(0, scrn_h - 21, scrn_w, 1, 5);
    fill_box(0, scrn_h - 20, scrn_w, 20, 7);
}
