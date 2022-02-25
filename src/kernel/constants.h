#pragma once

#include <cstdint>
#include "queue.h"

extern uint8_t* const vram;
extern const int scrn_w;
extern const int scrn_h;
extern const int g_size;

extern Queue mouse_buff;
extern Queue keyboard_buff;
struct Mouse {
    int button;
    int x, y;
};
extern Mouse mouse;

extern "C" {
    int get_gdt();
    int get_idt();
    int final();
}

template<class T>
void swap(T& t1, T& t2) {
    T t = t1;
    t1 = t2;
    t2 = t;
}

// #define max(a, b) (((a)-(b)<=0)?(b):(a))
// #define min(a, b) (((a)-(b)<=0)?(a):(b))
template<class T>
T max(const T& t1, const T& t2) {
    return t1 > t2 ? t1 : t2;
}

template<class T>
T min(const T& t1, const T& t2) {
    return t1 > t2 ? t2 : t1;
}

typedef char * va_list;
#define va_start(ap,p) (ap = (char *) (&(p)+1))
#define va_arg(ap, type) ((type *) (ap += sizeof(type)))[-1]
#define va_end(ap)

char * strcpy(char * dest,const char *src);
char * strcat(char * dest, const char * src);
unsigned int strlen(const char * s);
void * memset(void * s,int c,unsigned int count);
void * memcpy(void * dest,const void *src,unsigned int count);
int sprintf(char * str, const char *fmt, ...);
void itoa(unsigned int n, char * buf);
int atoi(char* pstr);
void xtoa(unsigned int n, char * buf);
int isDigit(unsigned char c);
int isLetter(unsigned char c);
