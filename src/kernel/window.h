#pragma once

#include "constants.h"
#include "graphics.h"
#include "fonts.h"

class Window {
private:
    Layer* content;
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
};

Window* create_window(int x, int y, int w, int h, const char title[]);