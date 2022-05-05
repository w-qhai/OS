#pragma once

#include "graphics.h"
#include "fonts.h"

#include "../lib/list.hpp"
#include "../lib/constants.h"

class Window {
public:   
    static Window* windows[1024];
    static int count;
    int wid;
    lm::Layer* back;
    int x;
    int y;
    int bg;
    int width;
    int height;
    char* title;
    Point cursor_pos;
    bool is_active;
    int curx, cury; // 输入游标所在位置

public:
    friend Window* create_window(int x, int y, int w, int h, const char title[]);
    inline lm::Layer* layer() {
        return this->back;
    }
    void show();
    void activate();
    void deactivate();
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