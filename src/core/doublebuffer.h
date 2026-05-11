#ifndef CORE_DOUBLEBUFFER_H
#define CORE_DOUBLEBUFFER_H

#include <graphics.h>

// Đơn giản hóa double buffering toàn game.
// Gọi beginFrame() đầu mỗi frame, vẽ tất cả lên buffer hiện tại,
// sau đó gọi endFrame() để hiển thị.

static int DB_CURRENT_PAGE = 0;

static void beginFrame() {
    // Đảo buffer: vẽ lên page mới, hiển thị page cũ
    DB_CURRENT_PAGE = 1 - DB_CURRENT_PAGE;
    setactivepage(DB_CURRENT_PAGE);
    setvisualpage(1 - DB_CURRENT_PAGE);
    cleardevice();
}

static void endFrame() {
    // Hiển thị page vừa vẽ
    setvisualpage(DB_CURRENT_PAGE);
}

#endif // CORE_DOUBLEBUFFER_H
