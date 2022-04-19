#include "window.h"

List<Window*, 1024> Window::windows;

Window* create_window(int x, int y, int w, int h, const char title[]) {
    Window* win = (Window*)mm::alloc(sizeof(Window));
    win->cursor_pos = {0, 0};   // 默认光标在0，0处
    win->back = lm::alloc((uint8_t*)mm::alloc(w*h), w, h, -1);

    lm::slide(win->back, x, y);

    win->x = x;
    win->y = y;
    win->width = w;
    win->height = h;
    win->title = (char*)mm::alloc(strlen(title)+1);
    for (int i = 0; title[i]; i++) {
        win->title[i] = title[i];
    }
    win->title[strlen(title)] = '\0';

    static char close_icon[14][17] = {
        "OOOOOOOOOOOOOOO@",
        "OQQQQQQQQQQQQQ$@",
        "OQQQQQQQQQQQQQ$@",
        "OQQQ@@QQQQ@@QQ$@",
        "OQQQQ@@QQ@@QQQ$@",
        "OQQQQQ@@@@QQQQ$@",
        "OQQQQQQ@@QQQQQ$@",
        "OQQQQQ@@@@QQQQ$@",
        "OQQQQ@@QQ@@QQQ$@",
        "OQQQ@@QQQQ@@QQ$@",
        "OQQQQQQQQQQQQQ$@",
        "OQQQQQQQQQQQQQ$@",
        "O$$$$$$$$$$$$$$@",
        "@@@@@@@@@@@@@@@@"
    };

    fill_box(0, 0, w, h, LightGrey, win->back);

    fill_box(0, 0, w, 1, LightGrey, win->back);         // 上边框线
    fill_box(0, 0, 1, h, LightGrey, win->back);         // 左边框线
    fill_box(w-1, 0, 1, h, LightGrey, win->back);       // 右边框线
    fill_box(0, h-1, w, 1, LightGrey, win->back);       // 下边框线

    fill_box(1, 1,      w-2, 1, White, win->back);      // 上边框线
    fill_box(1, 1,      1, h-2, White, win->back);      // 左边框线
    fill_box(1, h-2,    w-2, 1, DarkGrey, win->back);   // 下边框线
    fill_box(w-2, 1,    1, h-2, DarkGrey, win->back);   // 右边框线

    fill_box(2, 2,      w-4, 1, White, win->back);      // 上边框线
    fill_box(2, 2,      1, h-4, White, win->back);      // 左边框线
    fill_box(2, h-3,    w-4, 1, DarkGrey, win->back);   // 下边框线
    fill_box(w-3, 2,    1, h-4, DarkGrey, win->back);   // 右边框线
    
    fill_box(3, 3,      w-6, 20, Blue, win->back);    // 标题框
    draw_string((int)win, 5, 5, White, Blue, win->back); // 标题内容
    fill_box(3, 23,      w-6, h-27, LightGrey, win->back); // 内容框
    win->bg = LightGrey;


    // X
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 16; j++) {
            char c;
            switch (close_icon[i][j]) {
                case '@': c = Black; break;
                case '$': c = DarkGrey; break;
                case 'Q': c = LightGrey; break;
                default: c = White; break;
            }
            win->back->buff[(5+i)*win->back->width + (win->back->width-21+j)] = c;
        }
    }

    return win;
}
