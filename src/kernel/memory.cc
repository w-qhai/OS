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

// int MemoryManage::free(void* addr, uint32_t size) {
//     uint32_t i;
//     for (i = 0; i < this->capacity; i++) {
//         if (this->blocks[i].addr > (uint32_t)addr) {
//             break;
//         }
//     }

//     if (i > 0) {
//         if ()
//     }

// }
