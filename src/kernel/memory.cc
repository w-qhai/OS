#include "memory.h"

void MemoryManage::init() {
    this->unused = 0;
    this->capacity = 0;
    this->faild_count = 0;
    this->faild_total_size = 0;
}

uint32_t MemoryManage::total() {
    uint32_t sum = 0;
    for (uint32_t i = 0; i < this->unused; i++) {
        sum += this->blocks[i].size;
    }
    return sum;
}

void* MemoryManage::alloc(uint32_t size) {
    for (uint32_t i = 0; i < this->unused; i++) {
        if (this->blocks[i].size >= size) {
            uint32_t addr = this->blocks[i].addr;
            this->blocks[i].addr += size;
            this->blocks[i].size -= size;

            if (this->blocks[i].size == 0) {
                this->unused--;
                for (; i < this->unused; i++) {
                    this->blocks[i] = this->blocks[i + 1];
                }
            }
            return (void*)addr;
        }
    }
    return nullptr;
}

int MemoryManage::free(void* addr, uint32_t size) {
    uint32_t i, iaddr = (uint32_t)addr;
    for (i = 0; i < this->capacity; i++) {
        if (this->blocks[i].addr > (uint32_t)addr) {
            break;
        }
    }

    if (i > 0) {
        if (blocks[i-1].addr + blocks[i-1].size == iaddr) {
            blocks[i-1].size += size;
            if (i < this->unused) {
                if (iaddr + size == blocks[i].addr) {
                    blocks[i-1].size += blocks[i].size;
                    unused--;
                }
                for (; i < this->unused; i++) {
                    blocks[i] = blocks[i+1];
                }
            }
        }
        return 0;
    }

    if (i < this->unused) {
        if (iaddr + size == blocks[i].addr) {
            blocks[i].addr += iaddr;
            blocks[i].size += size;
            return 0;
        }
    }

    // 需要新建
    if (1) {
        for (uint32_t j = this->unused; j > i; j--) {
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
