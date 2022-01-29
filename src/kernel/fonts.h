#pragma once

#include <cstdint>
#include "fonts.h"
#include "constants.h"

extern uint8_t fonts[256][16];
void draw_char(char c, int x, int y, int color);
void draw_string(const char* str, int x, int y, int color);
void draw_number(int num, int base, int x, int y, int color);
