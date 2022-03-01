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
    Window();
    ~Window();
};