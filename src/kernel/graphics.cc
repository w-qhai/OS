#include "graphics.h"

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
