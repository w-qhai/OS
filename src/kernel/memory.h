#pragma once
#include "constants.h"
#include "list.hpp"

struct MemoryBlock {
    uint32_t addr;
    uint32_t size;
};

class MemoryManager {

public:
    static uint32_t size;
    
private:
    static List<MemoryBlock, 2048> blocks;

public:
    static void init();
    static uint32_t total();
    static void* alloc(uint32_t size);
    static int free(void* addr, uint32_t size);
};

