#ifndef ENTITY_ENEMY_H
#define ENTITY_ENEMY_H

#include <graphics.h>
#include <windows.h>
#include <math.h>
#include "../config.h"
#include "../core/primitives.h"

// ============================================================
//  Bullet - đạn bắn ra từ quái vật
// ============================================================
struct Bullet {
    float x, y;
    float vx, vy;
    bool active;
};

// ============================================================
//  Hằng số Player Bullet (đạn của người chơi - nhanh hơn đạn quái)
// ============================================================
static const int   MAX_PLAYER_BULLETS  = 16;
static const float PLAYER_BULLET_SPEED = 10.0f;   // px/frame
static const int   ROCKET_COOLDOWN_MAX = 50;       // frames (~0.8s @ 60fps)

// ============================================================
//  Enemy - quái vật bắn đạn
// ============================================================
struct Enemy {
    int   x, y;          // Tọa độ tâm chân
    int   width, height;
    bool  facingRight;   // Hướng nhìn (cũng là hướng bắn)
    int   shootTimer;    // Đếm ngược frame đến lần bắn tiếp theo
    int   shootCooldown; // Số frame giữa 2 lần bắn
    bool  active;
    // Di chuyển
    bool  canMove;       // Có thể di chuyển không
    float vx;            // Vận tốc ngang
    int   moveRange;     // Phạm vi di chuyển (pixels)
    int   startX;        // Vị trí xuất phát
};

// ============================================================
//  Hằng số
// ============================================================
static const int MAX_ENEMIES = 8;
static const int MAX_BULLETS = 32;
static const float BULLET_SPEED = 6.0f;
static const int BULLET_RADIUS  = 5;
static const int ENEMY_W = 28;
static const int ENEMY_H = 32;

// ============================================================
//  Khởi tạo một enemy
//  canMove: có thể di chuyển qua lại không
//  moveRange: phạm vi di chuyển (pixels)
// ============================================================
static Enemy makeEnemy(int x, int y, bool facingRight, int cooldown = 90, 
                       bool canMove = false, int moveRange = 100) {
    Enemy e;
    e.x = x; e.y = y;
    e.width = ENEMY_W; e.height = ENEMY_H;
    e.facingRight = facingRight;
    e.shootTimer   = cooldown / 2; // Lệch pha để không bắn đồng loạt
    e.shootCooldown = cooldown;
    e.active = true;
    e.canMove = canMove;
    e.vx = canMove ? 2.0f : 0.0f;
    e.moveRange = moveRange;
    e.startX = x;
    return e;
}

// ============================================================
//  Vẽ enemy (pixel-art: giống player nhưng màu đỏ/xám)
// ============================================================
static void drawEnemy(const Enemy& e) {
    if (!e.active) return;

    int x1 = e.x - e.width / 2;
    int x2 = e.x + e.width / 2;
    int y2 = e.y;
    int y1 = e.y - e.height;

    int bodyColor  = COLOR(180, 30, 30);    // Đỏ thân
    int armorColor = COLOR(80, 80, 90);     // Giáp xám
    int eyeColor   = COLOR(255, 220, 0);    // Mắt vàng
    int legColor   = COLOR(50, 50, 60);     // Chân đen
    int hornColor  = COLOR(200, 60, 0);     // Sừng cam

    int headH  = e.height * 2 / 5;
    int bodyH  = e.height * 2 / 5;
    int bodyTop= y2 - e.height / 5 - bodyH;
    int headBot= bodyTop;
    int headTop= headBot - headH;

    // Thân (giáp)
    setfillstyle(SOLID_FILL, armorColor);
    bar(x1 + 4, bodyTop, x2 - 4, y2 - e.height / 5);

    // Chân
    setfillstyle(SOLID_FILL, legColor);
    bar(x1 + 4, y2 - e.height / 5, x2 - 4, y2 - 3);

    // Đầu
    setfillstyle(SOLID_FILL, bodyColor);
    bar(x1 + 5, headTop + 2, x2 - 5, headBot - 1);

    // Sừng
    setcolor(HEX2COLOR(0xCC3300));
    setfillstyle(SOLID_FILL, hornColor);
    int hx = e.facingRight ? (x2 - 7) : (x1 + 7);
    int pts[8] = { hx - 4, headTop + 4, hx + 4, headTop + 4,
                   hx,     headTop - 6, hx - 4, headTop + 4 };
    fillpoly(4, pts);

    // Mắt sáng
    setfillstyle(SOLID_FILL, eyeColor);
    int eyeY = headTop + headH / 2;
    if (e.facingRight) {
        bar(x2 - 9, eyeY - 2, x2 - 5, eyeY + 2);
    } else {
        bar(x1 + 5, eyeY - 2, x1 + 9, eyeY + 2);
    }

    // Viền
    setcolor(COLOR(20, 0, 0));
    rectangle(x1 + 3, headTop, x2 - 3, y2);

    // Vũ khí (thanh kiếm mini)
    setcolor(COLOR(180, 180, 200));
    setlinestyle(SOLID_LINE, 0, 2);
    if (e.facingRight) {
        line(x2 - 4, bodyTop + 4, x2 + 10, bodyTop + 10);
    } else {
        line(x1 + 4, bodyTop + 4, x1 - 10, bodyTop + 10);
    }
    setlinestyle(SOLID_LINE, 0, 1);
}

// ============================================================
//  Vẽ đạn
// ============================================================
static void drawBullet(const Bullet& b) {
    if (!b.active) return;
    int bx = static_cast<int>(b.x);
    int by = static_cast<int>(b.y);

    // Nhân đạn phát sáng: lõi trắng + viền đỏ
    setfillstyle(SOLID_FILL, COLOR(255, 80, 0));
    fillellipse(bx, by, BULLET_RADIUS + 2, BULLET_RADIUS + 2);
    setfillstyle(SOLID_FILL, COLOR(255, 220, 100));
    fillellipse(bx, by, BULLET_RADIUS - 1, BULLET_RADIUS - 1);
}

// ============================================================
//  Update enemy (bắn đạn khi đến lượt + di chuyển)
//  bullets[]: mảng đạn toàn cục
//  numBullets: số phần tử trong mảng
// ============================================================
static void updateEnemy(Enemy& e, Bullet bullets[], int numBullets) {
    if (!e.active) return;
    
    // Di chuyển qua lại
    if (e.canMove) {
        e.x += static_cast<int>(e.vx);
        
        // Đảo chiều khi ra khỏi phạm vi
        if (e.x > e.startX + e.moveRange) {
            e.x = e.startX + e.moveRange;
            e.vx = -e.vx;
            e.facingRight = false;
        } else if (e.x < e.startX - e.moveRange) {
            e.x = e.startX - e.moveRange;
            e.vx = -e.vx;
            e.facingRight = true;
        }
    }
    
    // Bắn đạn
    e.shootTimer--;
    if (e.shootTimer <= 0) {
        e.shootTimer = e.shootCooldown;

        // Tìm slot đạn rảnh
        for (int i = 0; i < numBullets; ++i) {
            if (!bullets[i].active) {
                bullets[i].active = true;
                bullets[i].x = static_cast<float>(e.x);
                bullets[i].y = static_cast<float>(e.y - e.height / 2);
                bullets[i].vx = e.facingRight ? BULLET_SPEED : -BULLET_SPEED;
                bullets[i].vy = 0.0f;
                break;
            }
        }
    }
}

// ============================================================
//  Update đạn (di chuyển + kiểm tra ra khỏi màn hình)
// ============================================================
static void updateBullet(Bullet& b) {
    if (!b.active) return;
    b.x += b.vx;
    b.y += b.vy;

    // Ra ngoài màn hình -> hủy
    if (b.x < 0 || b.x > SCREEN_WIDTH || b.y < 0 || b.y > SCREEN_HEIGHT) {
        b.active = false;
    }
}

// ============================================================
//  Kiểm tra đạn có trúng player không (AABB)
// ============================================================
static bool bulletHitsPlayer(const Bullet& b, int px1, int py1, int px2, int py2) {
    if (!b.active) return false;
    int bx = static_cast<int>(b.x);
    int by = static_cast<int>(b.y);
    return !(bx + BULLET_RADIUS < px1 || bx - BULLET_RADIUS > px2 ||
             by + BULLET_RADIUS < py1 || by - BULLET_RADIUS > py2);
}

// ============================================================
//  Vẽ đạn của Player (xanh cyan, khác màu đạn quái đỏ-cam)
// ============================================================
static void drawPlayerBullet(const Bullet& b) {
    if (!b.active) return;
    int bx = static_cast<int>(b.x);
    int by = static_cast<int>(b.y);
    // Lớp ngoài xanh biển
    setfillstyle(SOLID_FILL, COLOR(0, 150, 255));
    fillellipse(bx, by, BULLET_RADIUS + 2, BULLET_RADIUS + 2);
    // Lớp trong trắng sáng
    setfillstyle(SOLID_FILL, COLOR(200, 240, 255));
    fillellipse(bx, by, BULLET_RADIUS - 1, BULLET_RADIUS - 1);
}

// ============================================================
//  Kiểm tra đạn player có trúng enemy không (AABB)
// ============================================================
static bool playerBulletHitsEnemy(const Bullet& b, const Enemy& e) {
    if (!b.active || !e.active) return false;
    int bx = static_cast<int>(b.x);
    int by = static_cast<int>(b.y);
    int ex1 = e.x - e.width / 2, ex2 = e.x + e.width / 2;
    int ey1 = e.y - e.height,    ey2 = e.y;
    return !(bx + BULLET_RADIUS < ex1 || bx - BULLET_RADIUS > ex2 ||
             by + BULLET_RADIUS < ey1 || by - BULLET_RADIUS > ey2);
}

// ============================================================
//  Helper: Lấy hướng từ player đến chuột (normalized)
// ============================================================
struct MouseDir {
    float dx, dy;  // vector đơn vị hướng player -> chuột
    int   mouseX, mouseY; // tọa độ chuột trong cửa sổ game
};

static MouseDir getMouseDirection(int originX, int originY) {
    POINT pt;
    GetCursorPos(&pt);
    // Tìm cửa sổ game theo tiêu đề
    HWND hwnd = FindWindow(NULL, "Parkour 2D - Me Cung Phieu Luu");
    if (hwnd) ScreenToClient(hwnd, &pt);

    MouseDir md;
    md.mouseX = pt.x;
    md.mouseY = pt.y;

    float dx = (float)(pt.x - originX);
    float dy = (float)(pt.y - originY);
    float len = sqrtf(dx * dx + dy * dy);
    if (len < 1.0f) len = 1.0f;
    md.dx = dx / len;
    md.dy = dy / len;
    return md;
}

// ============================================================
//  Reset toàn bộ mảng đạn
// ============================================================
static void resetBullets(Bullet bullets[], int numBullets) {
    for (int i = 0; i < numBullets; ++i)
        bullets[i].active = false;
}

#endif // ENTITY_ENEMY_H
