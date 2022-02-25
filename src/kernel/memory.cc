#include "memory.h"

uint32_t MemoryManager::unused = 0;
uint32_t MemoryManager::capacity = 0;
uint32_t MemoryManager::faild_count = 0;
uint32_t MemoryManager::faild_total_size = 0;
MemoryBlock MemoryManager::blocks[MemBlockCnt];
uint32_t MemoryManager::size = 0;

MemoryManager::MemoryManager() {

}

void MemoryManager::init() {
    uint32_t ax = *(uint32_t*)(0x90002);
    uint32_t bx = *(uint32_t*)(0x90004);
    MemoryManager:size = (ax + bx); // 计算内存大小
}

uint32_t MemoryManager::total() {
    uint32_t sum = 0;
    for (uint32_t i = 0; i < unused; i++) {
        sum += blocks[i].size;
    }
    return sum;
}

void* MemoryManager::alloc(uint32_t size) {
    for (uint32_t i = 0; i < unused; i++) {
        if (blocks[i].size >= size) {
            uint32_t addr = blocks[i].addr;
            blocks[i].addr += size;
            blocks[i].size -= size;

            if (blocks[i].size == 0) {
                unused--;
                for (; i < unused; i++) {
                    blocks[i] = blocks[i + 1];
                }
            }
            return (void*)addr;
        }
    }
    return nullptr;
}

int MemoryManager::free(void* addr, uint32_t size) {
    uint32_t i, iaddr = (uint32_t)addr;
    for (i = 0; i < capacity; i++) {
        if (blocks[i].addr > (uint32_t)addr) {
            break;
        }
    }

    if (i > 0) {
        if (blocks[i-1].addr + blocks[i-1].size == iaddr) {
            blocks[i-1].size += size;
            if (i < unused) {
                if (iaddr + size == blocks[i].addr) {
                    blocks[i-1].size += blocks[i].size;
                    unused--;
                }
                for (; i < unused; i++) {
                    blocks[i] = blocks[i+1];
                }
            }
        }
        return 0;
    }

    if (i < unused) {
        if (iaddr + size == blocks[i].addr) {
            blocks[i].addr += iaddr;
            blocks[i].size += size;
            return 0;
        }
    }

    // 需要新建
    if (1) {
        for (uint32_t j = unused; j > i; j--) {
            blocks[j] = blocks[j-1];
        }
        unused++;
        if (capacity < unused) {
            capacity = unused;
        }
        blocks[i] = {iaddr, size};
        return 0;
    }

    faild_count++;
    faild_total_size += size;
    return -1;
}
