#pragma once

#include "constants.h"
#include "memory.h"

#define Max_Layer   256
struct Layer {
    uint8_t* buff = nullptr;
    int x = 0, y = 0;
    int width = 0, height = 0;
    int alpha = -1;
    int z_index = -1;
    int flags = 0;

    void set_buff(uint8_t* buff, int width, int height, int alpha);
};

class LayerManager {
public:
    static int32_t top;
    static Layer* sheets[Max_Layer];
    static Layer sheets0[Max_Layer];

public:
    LayerManager();
    static Layer* alloc(uint8_t* buff, int width, int height, int alpha);
    static void updown(Layer* layer, int z_index);
    static void refresh(int x, int y, int w, int h, int z_index);
    static void slide(Layer* layer, int x, int y); 
    static void free(Layer* layer);
};