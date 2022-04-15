#pragma once

#include "constants.h"
#include "memory.h"
#define Max_Layer   256

namespace lm {
    struct Layer {
        uint8_t* buff = nullptr;
        int x = 0, y = 0;
        int width = 0, height = 0;
        int alpha = -1;
        int z_index = -1;
        int flags = 0;

        void set_buff(uint8_t* buff, int width, int height, int alpha);
    };

    static int32_t top = 0;
    static Layer* sheets[Max_Layer];
    static Layer sheets0[Max_Layer];
    static uint8_t* map_vram;
    // static List<Layer, 2048> blocks;

    void init(int w, int h);
    Layer* alloc(uint8_t* buff, int width, int height, int alpha);
    void updown(Layer* layer, int z_index);
    void refresh(int x, int y, int w, int h, int z_index);
    void slide(Layer* layer, int x, int y); 
    void free(Layer* layer);

    void refresh_map(int x, int y, int w, int h, int z_index);
};