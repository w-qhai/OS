#pragma once

#include <cstdint>

#define curosr_size 16

struct GDT_Descriptor
{
    uint16_t limit_low, base_low;
    uint8_t base_mid, more_flags;
    uint8_t limit_high, base_high;
};

struct IDT_Descriptor {
    uint16_t offset_low, selector;
    uint8_t dw_count, more_flags;
    uint16_t offset_high;
};

void set_gdt_seg(GDT_Descriptor* gdt, int limit, int base, int more_flags);
void set_idt_seg(IDT_Descriptor* idt, int offset, int selector, int more_flags);

extern uint8_t* vram;
extern int scrn_w;
extern int scrn_h;

extern "C" {
    GDT_Descriptor* get_gdt();
    IDT_Descriptor* get_idt();
    int final();
}

template<class T>
void swap(T& t1, T& t2) {
    T t = t1;
    t1 = t2;
    t2 = t;
}

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
int strcmp(const char *cs, const char *ct);
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
