#pragma once
#include "constants.h"
#include "list.hpp"

namespace mm {
    struct MemoryBlock {
        uint32_t addr;
        uint32_t size;
    };

    static uint32_t size;
    static List<MemoryBlock, 2048> blocks;

    void init();
    uint32_t total();
    uint32_t empty();
    void* alloc(uint32_t size);
    int free(void* addr, uint32_t size);
};

