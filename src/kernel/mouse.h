#pragma once

#include "constants.h"
#include "asmfun.h"
#include "graphics.h"
#include "fonts.h"

void enable_mouse();
void mouse_decode(const int8_t data[]);
extern bool is_mouse_init; 