#include "asmfun.h"
#include "fonts.h"
#include "constants.h"

#include <cstdlib>
// 显存 0xa0000~0xaffff

char str[20] = "sSsSs";
int main(void) {
    draw_char(0, 10, 10, 0);
    draw_string(str, 10, 26, 5);
    while(1);
    
    return 0;
}
