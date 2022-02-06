#pragma once
#include <cstdint>

struct Queue
{
    uint8_t     _buff[128];
    uint32_t    _front;
    uint32_t    _rear;
    uint32_t    _size;

    void push(uint8_t value);
    void pop();
    uint8_t front();
    void clear();
    bool empty();
};
