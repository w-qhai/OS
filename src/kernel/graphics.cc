#include "graphics.h"

void fill_box(int x, int y, int w, int h, int color, lm::Layer* layer) {
    w = min(w+x, layer->width);
    h = min(h+y, layer->height);
    for (int i = y; i < h; i++) {
        for (int j = x; j < w; j++) {
            layer->buff[i*layer->width + j] = color;
        }
    }
    lm::refresh(layer->x + x, layer->y + y, w, h, layer->z_index);
}

void draw_cursor(int x, int y, lm::Layer* layer) {
    static uint8_t cursor[curosr_size][curosr_size+1] = {
        "*...............",
        "**..............",
        "*O*.............",
        "*OO*............",
        "*OOO*...........",
        "*OOOO*..........",
        "*OOOOO*.........",
        "*OOOOOO*........",
        "*OOOOOOO*.......",
        "*OOOO*****......",
        "*OO*O*..........",
        "*O*.*O*.........",
        "**..*O*.........",
        "*....*O*........",
        ".....*O*........",
        "......*........."
    };

    for (int i = 0; i < curosr_size; i++) {
        for (int j = 0; j < curosr_size; j++) {
            if (cursor[i][j] == '*') {
                layer->buff[i*curosr_size+j] = 0;
            }
            if (cursor[i][j] == 'O') {
                layer->buff[i*curosr_size+j] = 15;
            }
            if (cursor[i][j] == '.') {
                layer->buff[i*curosr_size+j] = layer->alpha;
            }
        }
    }
    lm::refresh(layer->x + x, layer->y + y, curosr_size, curosr_size, 0);
}

void draw_desktop(lm::Layer* layer) {
    fill_box(0, 0, scrn_w, scrn_h, DarkBlue, layer);
    fill_box(0, scrn_h - 21, scrn_w, 1, 5, layer);
    fill_box(0, scrn_h - 20, scrn_w, 20, 7, layer);
}
