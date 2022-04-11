#include "memory.h"

uint32_t MemoryManager::size;
List<MemoryBlock, 2048> MemoryManager::blocks;


void MemoryManager::init() {
    uint32_t ax = *(uint16_t*)(0x90002);
    uint32_t bx = *(uint16_t*)(0x90004);
    size = (ax + bx * 64) * 1024; // 计算内存大小
    MemoryBlock all = {0, size};
    blocks.insert(0, all);
    alloc(1474560);
}

uint32_t MemoryManager::total() {
    uint32_t sum = 0;
    for (int i = 0; i < blocks.size(); i++) {
        sum += blocks.at(i).size;
    }
    return sum;
}

void* MemoryManager::alloc(uint32_t size) {
    int bsize = blocks.size();
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks.at(i).size >= size) {
            uint32_t addr = blocks.at(i).addr;
            
            blocks.at(i).addr += size;
            blocks.at(i).size -= size;

            if (blocks.at(i).size == 0) {
                blocks.remove(i);
            }
            return (void*)addr;
        }
    }
    return nullptr;
}

int MemoryManager::free(void* addr, uint32_t size) {
    uint32_t i, iaddr = (uint32_t)addr;
    for (i = 0; i < blocks.size(); i++) {
        if (blocks.at(i).addr > iaddr) {
            MemoryBlock block = {iaddr, size};
            blocks.insert(i, block);

            if (blocks.at(i).addr + blocks.at(i).size == blocks.at(i+1).addr) {
                blocks.at(i).size += blocks.at(i+1).size;
                blocks.remove(i+1);
            }
            if (blocks.at(i-1).addr + blocks.at(i-1).size == blocks.at(i).addr) {
                blocks.at(i-1).size += blocks.at(i).size;
                blocks.remove(i);
            }
            break;
        }
    }
    return -1;
}
