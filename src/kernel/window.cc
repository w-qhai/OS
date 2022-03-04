#include "window.h"

Window::Window()
{

}

Window::~Window() {

}

Window* create_window(int x, int y, int w, int h, const char title[]) {
    Window* win = (Window*)MemoryManager::alloc(sizeof(Window));
    win->back = LayerManager::alloc((uint8_t*)MemoryManager::alloc(w*h), w, h, -1);

    LayerManager::slide(win->back, x, y);
    LayerManager::updown(win->back, Max_Layer);

    // win->content = LayerManager::alloc((uint8_t*)MemoryManager::alloc((w-5)*(h-25)), w-5, h-25, 99);
    // for (int i = 0; i < (w-5)*(h-25); i++) {
    //     win->content->buff[i] = win->content->alpha;
    // }
    // LayerManager::slide(win->content, x+5, y+25);
    // LayerManager::updown(win->content, Max_Layer);

    win->x = x;
    win->y = y;
    win->width = w;
    win->height = h;
    win->title = (char*)MemoryManager::alloc(strlen(title));
    for (int i = 0; title[i]; i++) {
        win->title[i] = title[i];
    }

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

    fill_box(0, 0,      w, 1, LightGrey, win->back);
    fill_box(1, 1,      w-1, 2, White, win->back);
    fill_box(0, 0,      1, h, LightGrey, win->back);
    fill_box(1, 1,      2, h-1, White, win->back);
    fill_box(w-2, 1,    w-1, h-1, LightGrey, win->back); 
    fill_box(w-1, 0,    w, h, DarkGrey, win->back);
    fill_box(2, 2,      w-3, h-3, Black, win->back); // darkgrey
    fill_box(3, 3,      w-5, 20, Black, win->back); // Blue
    fill_box(1, h-2,    w-1, h-1, DarkGrey, win->back);
    fill_box(0, h-1,    w, h, Black, win->back);
    fill_box(2, 23, w-3, 1, DarkGrey, win->back);

    draw_string(title, 5, 5, White, win->back);
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

    LayerManager::refresh(x, y, w, h, win->back->z_index);
    return win;
}