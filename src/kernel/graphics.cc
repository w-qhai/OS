#include "graphics.h"

void fill_box(int x, int y, int w, int h, int color, Layer* layer) {
    for (int i = y; i < y + h; i++) {
        for (int j = x; j < x + w; j++) {
            layer->buff[i*layer->width + j] = color;
        }
    }
    LayerManager::refresh(layer->x + x, layer->y + y, w, h);
}

void draw_cursor(int x, int y, Layer* layer) {
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
    LayerManager::refresh(layer->x + x, layer->y + y, curosr_size, curosr_size);
}

void draw_desktop(Layer* layer) {
    fill_box(0, 0, scrn_w, scrn_h, 0x0f, layer);
    int white_count = 7;
    int white_width = scrn_w / white_count;
    for (int i = 1; i < white_count; i++) {
        fill_box(i * white_width, 0, 1, scrn_h, 0, layer);
    }

    int black_width = white_width * 2 / 3;
    for (int i = 1; i < white_count; i++) {
        if ((i + 1) % 4 == 0) {
            continue;
        }
        fill_box(i * white_width - black_width / 2, 0, black_width, scrn_h * 2 / 3, 0, layer);
    }

    fill_box(0, scrn_h - 21, scrn_w, 1, 5, layer);
    fill_box(0, scrn_h - 20, scrn_w, 20, 7, layer);
}
