#ifndef CORE_DOUBLEBUFFER_H
#define CORE_DOUBLEBUFFER_H

#include <graphics.h>

// đơn giản hóa double buffering toàn game
// gọi beginFrame
// sau đó gọi endFrame

static int DB_CURRENT_PAGE = 0;

static void beginFrame() {
    // đảo buffer
    DB_CURRENT_PAGE = 1 - DB_CURRENT_PAGE;
    setactivepage(DB_CURRENT_PAGE);
    setvisualpage(1 - DB_CURRENT_PAGE);
    cleardevice(); // phải clear để không bị chồng
}

static void endFrame() {
    // hiển thị page vừa vẽ
    setvisualpage(DB_CURRENT_PAGE);
}

#endif // cORE_DOUBLEBUFFER_H
