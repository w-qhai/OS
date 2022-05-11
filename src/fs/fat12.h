#pragma once

#include <cstdint>


struct FileInfo {
    uint8_t reserve1[0x20];
    char name[8], ext[3], type;
    uint8_t reserve2[10];
    uint16_t time, data, clustno;
    uint32_t size;
};

extern FileInfo* disk_addr;