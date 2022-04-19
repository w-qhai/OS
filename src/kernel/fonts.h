#pragma once

#include <cstdint>
#include "constants.h"
#include "layer.h"

class Window;

extern uint8_t fonts[256][16];
void draw_char(char c, int x, int y, int color, int bg, lm::Layer* layer);
void draw_string(const char* str, int x, int y, int color, int bg, lm::Layer* layer);
void draw_string(const char* str, int x, int y, int color, Window* win);

void draw_string(const int num, int x, int y, int color, int bg, lm::Layer* layer);
void draw_string(const int num, int x, int y, int color, Window* win);