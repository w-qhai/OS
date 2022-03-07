#pragma once
#include "constants.h"

#define MemBlockCnt 10

struct MemoryBlock {
    uint32_t addr;
    uint32_t size;
};

class MemoryManager {

public:
    static uint32_t size;

    static uint32_t unused;
    static uint32_t capacity;
    static uint32_t faild_total_size;
    static uint32_t faild_count;
    static MemoryBlock blocks[MemBlockCnt];

public:
    MemoryManager();
    static void init();
    static uint32_t total();
    static void* alloc(uint32_t size);
    static int free(void* addr, uint32_t size);
};

