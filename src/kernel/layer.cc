#include "layer.h"

void lm::Layer::set_buff(uint8_t* buff, int width, int height, int alpha) {
    this->buff = buff;
    this->width = width;
    this->height = height;
    this->alpha = alpha;
}

void lm::init(int w, int h) {
    map_vram = (uint8_t*)mm::alloc(w * h);
}

lm::Layer* lm::alloc(uint8_t* buff, int width, int height, int alpha) {
    lm::Layer* layer = nullptr;
    for (int i = 0; i < Max_Layer; i++) {
        if (sheets0[i].flags == 0) {
            layer = sheets0 + i;
            layer->flags = 1;
            layer->z_index = -1;
            break;
        }
    }
    layer->set_buff(buff, width, height, alpha);
    return layer;
}

void lm::updown(lm::Layer* layer, int z_index) {
    int old_z_index = layer->z_index;   // 保存旧的层数，
    z_index = min(z_index, top);
    z_index = max(z_index, -1);         // 保证新的层数在合理范围内

    layer->z_index = z_index;           
    sheets[z_index] = layer;            

    if (old_z_index > z_index) { // 比以前低
        if (z_index >= 0) {
            for (int i = old_z_index; i > z_index; i--) {
                sheets[i] = sheets[i-1];
                sheets[i]->z_index = i;
            }
            sheets[z_index] = layer;
        }
        else {
            if (top > old_z_index) {
                for (int i = old_z_index; i < top; i++) {
                    sheets[i] = sheets[i+1];
                    sheets[i]->z_index = i;
                }
            }
            top--;
        }
    }        
    else if (old_z_index < z_index) { // 比以前高
        if (old_z_index >= 0) {
            for (int i = old_z_index; i < z_index; i++) {
                sheets[i] = sheets[i+1];
                sheets[i]->z_index = i;
            }
            sheets[z_index] = layer;
        }
        else {
            for (int i = top-1; i >= z_index; i--) {
                sheets[i+1] = sheets[i];
                sheets[i+1]->z_index = i + 1;
            }
            sheets[z_index] = layer;
            top++;
        }
    }
    refresh(layer->x, layer->y, layer->width, layer->height, layer->z_index);
}

// 从指定层开始 绘制指定区域
void lm::refresh(int x, int y, int w, int h, int z_index) {
    refresh_map(x, y, w, h, z_index);
    x = max(x, 0);
    y = max(y, 0);
    w = min(scrn_w - x, w);
    h = min(scrn_h - y, h);

    for (int z = z_index; z < top; z++) {
        lm::Layer* layer = sheets[z];
            
        int bx0 = x - layer->x;
        int by0 = y - layer->y;
        int bx1 = x + w - layer->x;
        int by1 = y + h - layer->y;

        bx0 = max(bx0, 0);
        by0 = max(by0, 0);

        bx1 = min(layer->width, bx1);
        by1 = min(layer->height, by1);

        for (int i = by0; i < by1; i++) {
            int ry = i + layer->y;
            for (int j = bx0; j < bx1; j++) {
                int rx = j + layer->x;
                if (map_vram[ry*scrn_w+rx] == layer-sheets0) {
                    ::vram[ry*scrn_w + rx] =
                        layer->buff[i*layer->width + j];
                }
            }
        }
    }
    if (top > 1) {
        lm::Layer* layer = sheets[1];
            
        int bx0 = x - layer->x;
        int by0 = y - layer->y;
        int bx1 = x + w - layer->x;
        int by1 = y + h - layer->y;

        bx0 = max(bx0, 0);
        by0 = max(by0, 0);

        bx1 = min(layer->width, bx1);
        by1 = min(layer->height, by1);

        for (int i = by0; i < by1; i++) {
            int ry = i + layer->y;
            for (int j = bx0; j < bx1; j++) {
                int rx = j + layer->x;
                if (map_vram[ry*scrn_w+rx] == layer-sheets0) {
                    ::vram[ry*scrn_w + rx] =
                        layer->buff[i*layer->width + j];
                }
            }
        }
    }
}

void lm::slide(lm::Layer* layer, int x, int y) {
    int old_x = layer->x;
    int old_y = layer->y;
    layer->x = x;
    layer->y = y;
    if (layer->z_index >= 0) {
        // refresh_map(old_x, old_y, layer->width, layer->height, 0);  // 绘制旧区域
        // refresh_map(x, y, layer->width, layer->height, layer->z_index); // 绘制新区域
        refresh(old_x, old_y, layer->width, layer->height, 0);  // 绘制旧区域
        refresh(x, y, layer->width, layer->height, layer->z_index); // 绘制新区域
    }
}

void lm::free(lm::Layer* layer) {
    if (layer->z_index >= 0) {
        updown(layer, -1);
    }
    layer->flags = 0;
}

void lm::refresh_map(int x, int y, int w, int h, int z_index) {
    x = max(x, 0);
    y = max(y, 0);
    w = min(scrn_w - x, w);
    h = min(scrn_h - y, h);

    for (int z = z_index; z < top; z++) {
        lm::Layer* layer = sheets[z];
            
        int bx0 = x - layer->x;
        int by0 = y - layer->y;
        int bx1 = x + w - layer->x;
        int by1 = y + h - layer->y;

        bx0 = max(bx0, 0);
        by0 = max(by0, 0);

        bx1 = min(layer->width, bx1);
        by1 = min(layer->height, by1);

        for (int i = by0; i < by1; i++) {
            int ry = i + layer->y;
            for (int j = bx0; j < bx1; j++) {
                int rx = j + layer->x;
                if (layer->buff[i*layer->width + j] != layer->alpha) {
                    map_vram[ry*scrn_w+rx] = layer-sheets0;
                }
            }
        }
    }
    if (top > 1) {
        lm::Layer* layer = sheets[1];
            
        int bx0 = x - layer->x;
        int by0 = y - layer->y;
        int bx1 = x + w - layer->x;
        int by1 = y + h - layer->y;

        bx0 = max(bx0, 0);
        by0 = max(by0, 0);

        bx1 = min(layer->width, bx1);
        by1 = min(layer->height, by1);

        for (int i = by0; i < by1; i++) {
            int ry = i + layer->y;
            for (int j = bx0; j < bx1; j++) {
                int rx = j + layer->x;
                if (layer->buff[i*layer->width + j] != layer->alpha) {
                    map_vram[ry*scrn_w+rx] = layer-sheets0;
                }
            }
        }
    }
}