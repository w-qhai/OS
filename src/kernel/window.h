#pragma once

#include "constants.h"
#include "graphics.h"
#include "fonts.h"
#include "list.hpp"

class Window {
public:   
    static List<Window*, 1024> windows;
    lm::Layer* back;
    int x;
    int y;
    int bg;
    int width;
    int height;
    char* title;
public:
    Point cursor_pos;
    friend Window* create_window(int x, int y, int w, int h, const char title[]);
    inline lm::Layer* layer() {
        return this->back;
    }
    inline void show() {
        lm::updown(this->back, Max_Layer);    // 置顶
        lm::refresh(x, y, width, height, this->back->z_index);
        // if (windows.count(this) == 0) {
        //     windows.append(this);
        // }
    }
    inline void move(int x, int y) {
        lm::slide(back, x, y);
        this->x = x;
        this->y = y;
    }
    inline int background_color() {
        return bg;
    }
};

Window* create_window(int x, int y, int w, int h, const char title[]);