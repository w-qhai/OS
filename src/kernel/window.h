#pragma once

#include "constants.h"
#include "graphics.h"
#include "fonts.h"

class Window {
private:
    Layer* back;
    int x;
    int y;
    int width;
    int height;
    char* title;
public:
    friend Window* create_window(int x, int y, int w, int h, const char title[]);
    Window();
    ~Window();
    inline Layer* layer() {
        return this->back;
    }
    inline void show() {
        LayerManager::updown(this->back, Max_Layer);    // 置顶
        LayerManager::refresh(x, y, width, height, this->back->z_index);
    }
};

Window* create_window(int x, int y, int w, int h, const char title[]);