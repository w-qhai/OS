#include "fonts.h"
uint8_t fonts[256][16] = {
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x38,0x44,0x82,0xaa,0xaa,0x82,0x82,0xaa,0x92,0x44,0x38,0x0,0x0,0x0},
	{0x0,0x0,0x38,0x7c,0xfe,0xd6,0xd6,0xfe,0xfe,0xd6,0xee,0x7c,0x38,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x6c,0xfe,0xfe,0xfe,0x7c,0x38,0x10,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x10,0x38,0x7c,0xfe,0x7c,0x38,0x10,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x10,0x38,0x54,0xfe,0x54,0x10,0x38,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x10,0x38,0x7c,0xfe,0xd6,0x10,0x38,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x18,0x3c,0x3c,0x18,0x0,0x0,0x0,0x0,0x0,0x0},
	{0xff,0xff,0xff,0xff,0xff,0xff,0xe7,0xc3,0xc3,0xe7,0xff,0xff,0xff,0xff,0xff,0xff},
	{0x0,0x0,0x0,0x0,0x0,0x3c,0x66,0x42,0x42,0x66,0x3c,0x0,0x0,0x0,0x0,0x0},
	{0xff,0xff,0xff,0xff,0xff,0xc3,0x99,0xbd,0xbd,0x99,0xc3,0xff,0xff,0xff,0xff,0xff},
	{0x0,0x10,0x38,0x54,0x92,0x10,0x10,0x38,0x44,0x82,0x82,0x82,0x44,0x38,0x0,0x0},
	{0x0,0x38,0x44,0x82,0x82,0x82,0x44,0x38,0x10,0x10,0xfe,0x10,0x10,0x10,0x0,0x0},
	{0x0,0x0,0xc,0xe,0xb,0xb,0xa,0x8,0x8,0x18,0x78,0xf8,0x70,0x0,0x0,0x0},
	{0x0,0x0,0x1f,0x1f,0x11,0x11,0x11,0x11,0x11,0x11,0x77,0xff,0x66,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x10,0x54,0x38,0x28,0x38,0x54,0x10,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x0,0x0},
	{0x0,0x2,0x6,0xe,0x1e,0x3e,0x7e,0xfe,0x7e,0x3e,0x1e,0xe,0x6,0x2,0x0,0x0},
	{0x0,0x0,0x10,0x38,0x54,0x92,0x10,0x10,0x10,0x92,0x54,0x38,0x10,0x0,0x0,0x0},
	{0x0,0x0,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x0,0x0,0x44,0x44,0x0,0x0},
	{0x0,0x3e,0x4a,0x8a,0x8a,0x8a,0x8a,0x4a,0x3a,0xa,0xa,0xa,0xa,0xa,0x0,0x0},
	{0x7c,0x82,0x40,0x20,0x38,0x44,0x82,0x82,0x82,0x44,0x38,0x8,0x4,0x82,0x7c,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfe,0xfe,0xfe,0x0,0x0},
	{0x0,0x0,0x10,0x38,0x54,0x92,0x10,0x10,0x10,0x92,0x54,0x38,0x10,0x7c,0x0,0x0},
	{0x0,0x10,0x38,0x54,0x92,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x0,0x0},
	{0x0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x92,0x54,0x38,0x10,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x10,0x8,0x4,0xfe,0x4,0x8,0x10,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x10,0x20,0x40,0xfe,0x40,0x20,0x10,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x80,0x80,0xfe,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x28,0x44,0xfe,0x44,0x28,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x10,0x10,0x38,0x38,0x7c,0x7c,0xfe,0xfe,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0xfe,0xfe,0x7c,0x7c,0x38,0x38,0x10,0x10,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x0,0x0,0x10,0x10,0x0,0x0},
	{0x28,0x28,0x28,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x44,0x44,0x44,0xfe,0x44,0x44,0x44,0x44,0x44,0xfe,0x44,0x44,0x44,0x0,0x0},
	{0x10,0x3a,0x56,0x92,0x92,0x90,0x50,0x38,0x14,0x12,0x92,0x92,0xd4,0xb8,0x10,0x10},
	{0x62,0x92,0x94,0x94,0x68,0x8,0x10,0x10,0x20,0x2c,0x52,0x52,0x92,0x8c,0x0,0x0},
	{0x0,0x70,0x88,0x88,0x88,0x90,0x60,0x47,0xa2,0x92,0x8a,0x84,0x46,0x39,0x0,0x0},
	{0x4,0x8,0x10,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x2,0x4,0x8,0x8,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x8,0x8,0x4,0x2,0x0},
	{0x80,0x40,0x20,0x20,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x20,0x20,0x40,0x80,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x10,0x92,0x54,0x38,0x54,0x92,0x10,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x10,0x10,0x10,0xfe,0x10,0x10,0x10,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x18,0x18,0x8,0x8,0x10},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfe,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x18,0x18,0x0,0x0},
	{0x2,0x2,0x4,0x4,0x8,0x8,0x8,0x10,0x10,0x20,0x20,0x40,0x40,0x40,0x80,0x80},
	{0x0,0x18,0x24,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x24,0x18,0x0,0x0},
	{0x0,0x8,0x18,0x28,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x3e,0x0,0x0},
	{0x0,0x18,0x24,0x42,0x42,0x2,0x4,0x8,0x10,0x20,0x20,0x40,0x40,0x7e,0x0,0x0},
	{0x0,0x18,0x24,0x42,0x2,0x2,0x4,0x18,0x4,0x2,0x2,0x42,0x24,0x18,0x0,0x0},
	{0x0,0xc,0xc,0xc,0x14,0x14,0x14,0x24,0x24,0x44,0x7e,0x4,0x4,0x1e,0x0,0x0},
	{0x0,0x7c,0x40,0x40,0x40,0x58,0x64,0x2,0x2,0x2,0x2,0x42,0x24,0x18,0x0,0x0},
	{0x0,0x18,0x24,0x42,0x40,0x58,0x64,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x0,0x0},
	{0x0,0x7e,0x42,0x42,0x4,0x4,0x8,0x8,0x8,0x10,0x10,0x10,0x10,0x38,0x0,0x0},
	{0x0,0x18,0x24,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x24,0x18,0x0,0x0},
	{0x0,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x26,0x1a,0x2,0x42,0x24,0x18,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x18,0x18,0x0,0x0,0x0,0x0,0x0,0x18,0x18,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x18,0x18,0x0,0x0,0x0,0x0,0x18,0x18,0x8,0x8,0x10},
	{0x0,0x2,0x4,0x8,0x10,0x20,0x40,0x80,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0xfe,0x0,0x0,0xfe,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x2,0x4,0x8,0x10,0x20,0x40,0x80,0x0},
	{0x0,0x38,0x44,0x82,0x82,0x82,0x4,0x8,0x10,0x10,0x0,0x0,0x18,0x18,0x0,0x0},
	{0x0,0x38,0x44,0x82,0x9a,0xaa,0xaa,0xaa,0xaa,0xaa,0x9c,0x80,0x46,0x38,0x0,0x0},
	{0x0,0x18,0x18,0x18,0x18,0x24,0x24,0x24,0x24,0x7e,0x42,0x42,0x42,0xe7,0x0,0x0},
	{0x0,0xf0,0x48,0x44,0x44,0x44,0x48,0x78,0x44,0x42,0x42,0x42,0x44,0xf8,0x0,0x0},
	{0x0,0x3a,0x46,0x42,0x82,0x80,0x80,0x80,0x80,0x80,0x82,0x42,0x44,0x38,0x0,0x0},
	{0x0,0xf8,0x44,0x44,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0x44,0xf8,0x0,0x0},
	{0x0,0xfe,0x42,0x42,0x40,0x40,0x44,0x7c,0x44,0x40,0x40,0x42,0x42,0xfe,0x0,0x0},
	{0x0,0xfe,0x42,0x42,0x40,0x40,0x44,0x7c,0x44,0x44,0x40,0x40,0x40,0xf0,0x0,0x0},
	{0x0,0x3a,0x46,0x42,0x82,0x80,0x80,0x9e,0x82,0x82,0x82,0x42,0x46,0x38,0x0,0x0},
	{0x0,0xe7,0x42,0x42,0x42,0x42,0x42,0x7e,0x42,0x42,0x42,0x42,0x42,0xe7,0x0,0x0},
	{0x0,0x7c,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7c,0x0,0x0},
	{0x0,0x1f,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x84,0x48,0x30,0x0},
	{0x0,0xe7,0x42,0x44,0x48,0x50,0x50,0x60,0x50,0x50,0x48,0x44,0x42,0xe7,0x0,0x0},
	{0x0,0xf0,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x42,0x42,0xfe,0x0,0x0},
	{0x0,0xc3,0x42,0x66,0x66,0x66,0x5a,0x5a,0x5a,0x42,0x42,0x42,0x42,0xe7,0x0,0x0},
	{0x0,0xc7,0x42,0x62,0x62,0x52,0x52,0x52,0x4a,0x4a,0x4a,0x46,0x46,0xe2,0x0,0x0},
	{0x0,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x0,0x0},
	{0x0,0xf8,0x44,0x42,0x42,0x42,0x44,0x78,0x40,0x40,0x40,0x40,0x40,0xf0,0x0,0x0},
	{0x0,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x92,0x8a,0x44,0x3a,0x0,0x0},
	{0x0,0xfc,0x42,0x42,0x42,0x42,0x7c,0x44,0x42,0x42,0x42,0x42,0x42,0xe7,0x0,0x0},
	{0x0,0x3a,0x46,0x82,0x82,0x80,0x40,0x38,0x4,0x2,0x82,0x82,0xc4,0xb8,0x0,0x0},
	{0x0,0xfe,0x92,0x92,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7c,0x0,0x0},
	{0x0,0xe7,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x3c,0x0,0x0},
	{0x0,0xe7,0x42,0x42,0x42,0x42,0x24,0x24,0x24,0x24,0x18,0x18,0x18,0x18,0x0,0x0},
	{0x0,0xe7,0x42,0x42,0x42,0x5a,0x5a,0x5a,0x5a,0x24,0x24,0x24,0x24,0x24,0x0,0x0},
	{0x0,0xe7,0x42,0x42,0x24,0x24,0x24,0x18,0x24,0x24,0x24,0x42,0x42,0xe7,0x0,0x0},
	{0x0,0xee,0x44,0x44,0x44,0x28,0x28,0x28,0x10,0x10,0x10,0x10,0x10,0x7c,0x0,0x0},
	{0x0,0xfe,0x84,0x84,0x8,0x8,0x10,0x10,0x20,0x20,0x40,0x42,0x82,0xfe,0x0,0x0},
	{0x0,0x3e,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3e,0x0},
	{0x80,0x80,0x40,0x40,0x20,0x20,0x20,0x10,0x10,0x8,0x8,0x4,0x4,0x4,0x2,0x2},
	{0x0,0x7c,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x7c,0x0},
	{0x0,0x10,0x28,0x44,0x82,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfe,0x0},
	{0x10,0x8,0x4,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x70,0x8,0x4,0x3c,0x44,0x84,0x84,0x8c,0x76,0x0,0x0},
	{0xc0,0x40,0x40,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x42,0x42,0x64,0x58,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x30,0x4c,0x84,0x84,0x80,0x80,0x82,0x44,0x38,0x0,0x0},
	{0xc,0x4,0x4,0x4,0x4,0x34,0x4c,0x84,0x84,0x84,0x84,0x84,0x4c,0x36,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x38,0x44,0x82,0x82,0xfc,0x80,0x82,0x42,0x3c,0x0,0x0},
	{0xe,0x10,0x10,0x10,0x10,0x7c,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7c,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x36,0x4c,0x84,0x84,0x84,0x84,0x4c,0x34,0x4,0x4,0x78},
	{0xc0,0x40,0x40,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x42,0x42,0x42,0xe3,0x0,0x0},
	{0x0,0x10,0x10,0x0,0x0,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x0,0x0},
	{0x0,0x4,0x4,0x0,0x0,0xc,0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x8,0x8,0x30},
	{0xc0,0x40,0x40,0x40,0x40,0x4e,0x44,0x48,0x50,0x60,0x50,0x48,0x44,0xe6,0x0,0x0},
	{0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0xf6,0x49,0x49,0x49,0x49,0x49,0x49,0x49,0xdb,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0xd8,0x64,0x42,0x42,0x42,0x42,0x42,0x42,0xe3,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0xd8,0x64,0x42,0x42,0x42,0x42,0x42,0x64,0x58,0x40,0xe0},
	{0x0,0x0,0x0,0x0,0x0,0x34,0x4c,0x84,0x84,0x84,0x84,0x84,0x4c,0x34,0x4,0xe},
	{0x0,0x0,0x0,0x0,0x0,0xdc,0x62,0x42,0x40,0x40,0x40,0x40,0x40,0xe0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x7a,0x86,0x82,0xc0,0x38,0x6,0x82,0xc2,0xbc,0x0,0x0},
	{0x0,0x0,0x10,0x10,0x10,0x7c,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xe,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0xc6,0x42,0x42,0x42,0x42,0x42,0x42,0x46,0x3b,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0xe7,0x42,0x42,0x42,0x24,0x24,0x24,0x18,0x18,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0xe7,0x42,0x42,0x5a,0x5a,0x5a,0x24,0x24,0x24,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0xc6,0x44,0x28,0x28,0x10,0x28,0x28,0x44,0xc6,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0xe7,0x42,0x42,0x24,0x24,0x24,0x18,0x18,0x10,0x10,0x60},
	{0x0,0x0,0x0,0x0,0x0,0xfe,0x82,0x84,0x8,0x10,0x20,0x42,0x82,0xfe,0x0,0x0},
	{0x0,0x6,0x8,0x10,0x10,0x10,0x10,0x60,0x10,0x10,0x10,0x10,0x8,0x6,0x0,0x0},
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},
	{0x0,0x60,0x10,0x8,0x8,0x8,0x8,0x6,0x8,0x8,0x8,0x8,0x10,0x60,0x0,0x0},
	{0x0,0x72,0x8c,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x10,0x28,0x44,0x82,0xfe,0x82,0xfe,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x38,0x44,0x82,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x82,0x44,0x38,0x10,0x20},
	{0x0,0x0,0x24,0x24,0x0,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x42,0x3e,0x0,0x0},
	{0xc,0x8,0x10,0x0,0x0,0x38,0x44,0x82,0x82,0xfe,0x80,0x82,0x44,0x38,0x0,0x0},
	{0x0,0x10,0x28,0x44,0x0,0x78,0x4,0x4,0x3c,0x44,0x84,0x84,0x44,0x3e,0x0,0x0},
	{0x0,0x0,0x24,0x24,0x0,0x78,0x4,0x4,0x3c,0x44,0x84,0x84,0x44,0x3e,0x0,0x0},
	{0x10,0x8,0x4,0x0,0x0,0x78,0x4,0x4,0x3c,0x44,0x84,0x84,0x44,0x3e,0x0,0x0},
	{0x0,0x18,0x24,0x18,0x0,0x78,0x4,0x4,0x3c,0x44,0x84,0x84,0x44,0x3e,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x3c,0x42,0x80,0x80,0x80,0x80,0x80,0x42,0x3c,0x8,0x10},
	{0x0,0x10,0x28,0x44,0x0,0x38,0x44,0x82,0x82,0xfe,0x80,0x82,0x44,0x38,0x0,0x0},
	{0x0,0x0,0x24,0x24,0x0,0x38,0x44,0x82,0x82,0xfe,0x80,0x82,0x44,0x38,0x0,0x0},
	{0x10,0x8,0x4,0x0,0x0,0x38,0x44,0x82,0x82,0xfe,0x80,0x82,0x44,0x38,0x0,0x0},
	{0x0,0x0,0x24,0x24,0x0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x0,0x0},
	{0x0,0x10,0x28,0x44,0x0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x0,0x0},
	{0x10,0x8,0x4,0x0,0x0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x0,0x0},
	{0x24,0x24,0x0,0x38,0x44,0x82,0x82,0x82,0x82,0xfe,0x82,0x82,0x82,0x82,0x0,0x0},
	{0x0,0x38,0x44,0x38,0x44,0x82,0x82,0x82,0x82,0xfe,0x82,0x82,0x82,0x82,0x0,0x0},
	{0xc,0x8,0x10,0xfe,0x80,0x80,0x80,0x80,0xf8,0x80,0x80,0x80,0x80,0xfe,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x60,0x1c,0x12,0x72,0x9e,0x90,0x90,0x92,0x6c,0x0,0x0},
	{0xc,0x10,0x20,0x28,0x28,0x28,0xfe,0x28,0x28,0x28,0x28,0x28,0x28,0x28,0x0,0x0},
	{0x0,0x10,0x28,0x44,0x0,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x0,0x0},
	{0x0,0x0,0x24,0x24,0x0,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x0,0x0},
	{0x10,0x8,0x4,0x0,0x0,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x0,0x0},
	{0x0,0x10,0x28,0x44,0x0,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x42,0x3e,0x0,0x0},
	{0x10,0x8,0x4,0x0,0x0,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x42,0x3e,0x0,0x0},
	{0x0,0x0,0x24,0x24,0x0,0x82,0x82,0x44,0x44,0x28,0x28,0x10,0x10,0x20,0x20,0x40},
	{0x24,0x24,0x0,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x0,0x0},
	{0x24,0x24,0x0,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x0,0x0},
	{0x0,0x28,0x28,0x28,0x3c,0x6a,0xa8,0xa8,0xa8,0xa8,0xa8,0x6a,0x3c,0x28,0x28,0x28},
	{0x0,0xc,0x12,0x20,0x20,0x20,0xfc,0x20,0x20,0x20,0x60,0xa0,0xb2,0x4c,0x0,0x0},
	{0x0,0x82,0x82,0x44,0x28,0x10,0xfe,0x10,0x10,0xfe,0x10,0x10,0x10,0x10,0x0,0x0},
	{0x0,0xe0,0x90,0x88,0x88,0x88,0x94,0xe4,0x9f,0x84,0x84,0x84,0x84,0x84,0x0,0x0},
	{0x0,0xc,0x12,0x10,0x10,0x10,0xfe,0x10,0x10,0x10,0x10,0x10,0x90,0x60,0x0,0x0},
	{0xc,0x8,0x10,0x0,0x0,0x78,0x4,0x4,0x3c,0x44,0x84,0x84,0x44,0x3e,0x0,0x0},
	{0xc,0x8,0x10,0x0,0x0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x0,0x0},
	{0xc,0x8,0x10,0x0,0x0,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x0,0x0},
	{0xc,0x8,0x10,0x0,0x0,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x42,0x3e,0x0,0x0},
	{0x0,0x12,0x2a,0x24,0x0,0xf8,0x84,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x0,0x0},
	{0x12,0x2a,0x24,0x0,0x82,0xc2,0xc2,0xa2,0x92,0x92,0x8a,0x86,0x86,0x82,0x0,0x0},
	{0x0,0x0,0x0,0x78,0x4,0x4,0x3c,0x44,0x84,0x84,0x44,0x3e,0x0,0xfe,0x0,0x0},
	{0x0,0x0,0x0,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x0,0xfe,0x0,0x0},
	{0x0,0x10,0x10,0x0,0x0,0x10,0x10,0x20,0x44,0x82,0x82,0x82,0x44,0x38,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfe,0x80,0x80,0x80,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfe,0x2,0x2,0x2,0x0,0x0},
	{0x0,0x10,0x30,0x10,0x10,0x10,0x0,0xfe,0x0,0x78,0x4,0x38,0x40,0x7c,0x0,0x0},
	{0x0,0x10,0x30,0x10,0x10,0x10,0x0,0xfe,0x0,0x18,0x28,0x48,0x7c,0x8,0x0,0x0},
	{0x0,0x10,0x10,0x0,0x0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x12,0x24,0x48,0x90,0x90,0x48,0x24,0x12,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x90,0x48,0x24,0x12,0x12,0x24,0x48,0x90,0x0,0x0,0x0,0x0},
	{0x11,0x44,0x11,0x44,0x11,0x44,0x11,0x44,0x11,0x44,0x11,0x44,0x11,0x44,0x11,0x44},
	{0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa},
	{0x77,0xdd,0x77,0xdd,0x77,0xdd,0x77,0xdd,0x77,0xdd,0x77,0xdd,0x77,0xdd,0x77,0xdd},
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xf0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xf0,0x10,0xf0,0x10,0x10,0x10,0x10,0x10,0x10},
	{0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xf4,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfc,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf0,0x10,0xf0,0x10,0x10,0x10,0x10,0x10,0x10},
	{0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xf4,0x4,0xf4,0x14,0x14,0x14,0x14,0x14,0x14},
	{0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xfc,0x4,0xf4,0x14,0x14,0x14,0x14,0x14,0x14},
	{0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xf4,0x4,0xfc,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xfc,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xf0,0x10,0xf0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xf0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1f,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xff,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1f,0x10,0x1f,0x10,0x10,0x10,0x10,0x10,0x10},
	{0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x17,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14},
	{0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x17,0x10,0x1f,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0x10,0x17,0x14,0x14,0x14,0x14,0x14,0x14},
	{0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xf7,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xf7,0x14,0x14,0x14,0x14,0x14,0x14},
	{0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x17,0x10,0x17,0x14,0x14,0x14,0x14,0x14,0x14},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xf7,0x0,0xf7,0x14,0x14,0x14,0x14,0x14,0x14},
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xff,0x0,0xff,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x0,0xff,0x10,0x10,0x10,0x10,0x10,0x10},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14},
	{0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x1f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1f,0x10,0x1f,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0x10,0x1f,0x10,0x10,0x10,0x10,0x10,0x10},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14},
	{0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xf7,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14},
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xff,0x10,0xff,0x10,0x10,0x10,0x10,0x10,0x10},
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1f,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},
	{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
	{0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0},
	{0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf,0xf},
	{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
	{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}
};

void draw_char(char c, int x, int y, int color) {
    // 字体 16 * 8
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 8; j++) {
            if (fonts[c][i] & (0x80 >> j)) {
                vram[(y + i)* scrn_w + x + j] = color;
            }
        }
    }
}

void draw_string(char* str, int x, int y, int color) {
    for (int i = 0; str[i]; i++) {
        draw_char(str[i], x + i * 8, y, color);
    }
}

