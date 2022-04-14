#pragma once

#include "constants.h"
#include "graphics.h"
#include "fonts.h"

class Window {
private:
    lm::Layer* back;
    int x;
    int y;
    int width;
    int height;
    char* title;
public:
    friend Window* create_window(int x, int y, int w, int h, const char title[]);
    inline lm::Layer* layer() {
        return this->back;
    }
    inline void show() {
        lm::updown(this->back, Max_Layer);    // 置顶
        lm::refresh(x, y, width, height, this->back->z_index);
    }
};

Window* create_window(int x, int y, int w, int h, const char title[]);