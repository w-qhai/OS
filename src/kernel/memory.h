#pragma once
#include "constants.h"

struct MemoryBlock {
    uint32_t addr;
    uint32_t size;
};

struct MemoryManage {
    uint32_t unused;
    uint32_t capacity;
    uint32_t faild_total_size;
    uint32_t faild_count;
    MemoryBlock blocks[1000];

    void init();
    uint32_t total();
    void* alloc(uint32_t size);
    int free(void* addr, uint32_t size);
};

