#include "graphics.h"

void fill_box(Rect rect, int color, lm::Layer* layer) {
    fill_box(rect.x, rect.y, rect.w, rect.h, color, layer);
}

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

    Rect bg = {0, 0, scrn_w, scrn_h};
    fill_box(bg, DarkBlue, layer);    // 背景

    Rect tsk = {0, bg.h-bg.h/20, bg.w, bg.h/20};
    fill_box(tsk, LightGrey, layer); // 任务栏背景

    Rect splite_line = {0, bg.h-bg.h/20-2, bg.w, 2};
    fill_box(splite_line, White, layer); // 分割线

    Rect btn1 = {tsk.x+tsk.w/100, tsk.y+tsk.h/10, tsk.w/10, tsk.h-tsk.h/4};
    fill_box(btn1, White, layer);
    btn1.x += 2;
    btn1.y += 2;
    fill_box(btn1, DarkGrey, layer);
    btn1.w -= 2;
    btn1.h -= 2;
    fill_box(btn1, LightGrey, layer);

    Rect btn2 = {bg.w-btn1.x-btn1.w, tsk.y+tsk.h/10, tsk.w/10, tsk.h-tsk.h/4};
    fill_box(btn2, DarkGrey, layer);
    btn2.x += 2;
    btn2.y += 2;
    fill_box(btn2, White, layer);
    btn2.w -= 2;
    btn2.h -= 2;
    fill_box(btn2, LightGrey, layer);
}
