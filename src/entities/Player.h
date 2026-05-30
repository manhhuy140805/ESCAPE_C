#ifndef ENTITY_PLAYER_H
#define ENTITY_PLAYER_H

#include <graphics.h>
#include "../config.h"
#include "../graphics/CustomDrawing.h"

// player model
struct Player {
    int x;
    int y;
    int width;
    int height;
    bool facingRight;
    // vận tốc & trạng thái va chạm đơn giản
    float vx;
    float vy;
    bool onGround;
    // hP system
    int hp;
    int maxHp;
    int invincibleTimer; // thời gian bất tử sau khi bị trúng đạn
};

static Player makeDefaultPlayer(int startX, int startY) {
    Player p;
    p.x = startX;
    p.y = startY;
    p.width = 24;
    p.height = 32;
    p.facingRight = true;
    p.vx = 0.0f;
    p.vy = 0.0f;
    p.onGround = false;
    p.hp = 3;
    p.maxHp = 3;
    p.invincibleTimer = 0;
    return p;
}

// vẽ nhân vật chính theo style pixel
static void drawPlayer(const Player &p) {
    int w = p.width;
    int h = p.height;

    int x1 = p.x - w / 2;
    int x2 = p.x + w / 2;
    int y2 = p.y; // chân
    int y1 = p.y - h; // đỉnh đầu

    // nhấp nháy khi bất tử
    if (p.invincibleTimer > 0 && (p.invincibleTimer / 5) % 2 == 0) {
        return; // không vẽ để tạo hiệu ứng nhấp nháy
    }

    // màu cơ bản
    int skin   = COLOR(255, 220, 180);
    int shirt  = COLOR(40, 150, 60); // áo xanh lá
    int pants  = COLOR(30, 40, 80); // quần xanh đậm
    int shoes  = COLOR(60, 30, 10); // giày nâu
    int hair   = COLOR(80, 40, 20); // tóc nâu

    // thân
    int bodyH = h * 2 / 5;
    setfillstyle(SOLID_FILL, shirt);
    bar(x1 + 3, y2 - bodyH - h / 5, x2 - 3, y2 - h / 5);

    // chân
    int legTop = y2 - h / 5;
    setfillstyle(SOLID_FILL, pants);
    bar(x1 + 3, legTop, x2 - 3, y2 - 4);

    // giày
    setfillstyle(SOLID_FILL, shoes);
    bar(x1 + 3, y2 - 4, x1 + w / 2 - 1, y2);
    bar(x1 + w / 2 + 1, y2 - 4, x2 - 3, y2);

    // đầu
    int headH = h * 2 / 5;
    int headBottom = y2 - bodyH - h / 5;
    int headTop = headBottom - headH;
    setfillstyle(SOLID_FILL, skin);
    bar(x1 + 4, headTop + 2, x2 - 4, headBottom - 1);

    // tóc
    setfillstyle(SOLID_FILL, hair);
    bar(x1 + 4, headTop, x2 - 4, headTop + headH / 3);

    // mắt
    setcolor(0);
    if (p.facingRight) {
        line(x2 - 7, headTop + headH / 2, x2 - 5, headTop + headH / 2);
    } else {
        line(x1 + 5, headTop + headH / 2, x1 + 7, headTop + headH / 2);
    }

    // viền tổng thể nhẹ cho rõ hình
    setcolor(0);
    rectangle(x1 + 2, headTop, x2 - 2, y2);
}

// vẽ thanh HP
static void drawPlayerHP(const Player &p) {
    int heartSize = 20;
    int spacing = 25;
    int startX = 230;
    int startY = 15;

    for (int i = 0; i < p.maxHp; ++i) {
        int hx = startX + i * spacing;
        int hy = startY;
        
        if (i < p.hp) {
            // trái tim đỏ
            setfillstyle(SOLID_FILL, COLOR(255, 50, 50));
            setcolor(COLOR(200, 0, 0));
        } else {
            // trái tim xám
            setfillstyle(SOLID_FILL, COLOR(80, 80, 80));
            setcolor(COLOR(50, 50, 50));
        }
        
        // vẽ trái tim đơn giản
        fillellipse(hx - 5, hy, 5, 5);
        fillellipse(hx + 5, hy, 5, 5);
        int pts[8] = {
            hx - 10, hy,
            hx, hy + 12,
            hx + 10, hy,
            hx - 10, hy
        };
        fillpoly(4, pts);
        
        // viền
        circle(hx - 5, hy, 5);
        circle(hx + 5, hy, 5);
        line(hx - 10, hy, hx, hy + 12);
        line(hx + 10, hy, hx, hy + 12);
    }
}

#endif // eNTITY_PLAYER_H
