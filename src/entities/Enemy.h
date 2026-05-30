#ifndef ENTITY_ENEMY_H
#define ENTITY_ENEMY_H

#include <graphics.h>
#include <windows.h>
#include <math.h>
#include "../config.h"
#include "../core/primitives.h"
#include "../graphics/CustomDrawing.h"

// bullet
struct Bullet {
    float x, y;
    float vx, vy;
    bool active;
    bool isRocket;
};

// hằng số Player Bullet
static const int   MAX_PLAYER_BULLETS  = 16;
static const float PLAYER_BULLET_SPEED = 10.0f; // px/frame
static const int   ROCKET_COOLDOWN_MAX = 50; // frames

// enemy
struct Enemy {
    int   x, y; // tọa độ tâm chân
    int   width, height;
    bool  facingRight; // hướng nhìn
    int   shootTimer; // đếm ngược frame đến lần bắn tiếp theo
    int   shootCooldown; // số frame giữa 2 lần bắn
    bool  active;
    // di chuyển
    bool  canMove; // có thể di chuyển không
    float vx; // vận tốc ngang
    float vy; // vận tốc dọc
    bool  onGround; // đang đứng trên mặt đất
    int   moveRange; // phạm vi di chuyển
    int   startX; // vị trí xuất phát
};

// hằng số
static const int MAX_ENEMIES = 8;
static const int MAX_BULLETS = 32;
static const float BULLET_SPEED = 6.0f;
static const int BULLET_RADIUS  = 5;
static const int ENEMY_W = 28;
static const int ENEMY_H = 32;

// khởi tạo một enemy
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
    e.vy = 0.0f; // khởi tạo vận tốc dọc
    e.onGround = false; // khởi tạo trạng thái đất
    e.moveRange = moveRange;
    e.startX = x;
    return e;
}

// vẽ enemy
static void drawEnemy(const Enemy& e) {
    if (!e.active) return;

    int x1 = e.x - e.width / 2;
    int x2 = e.x + e.width / 2;
    int y2 = e.y;
    int y1 = e.y - e.height;

    int bodyColor  = COLOR(180, 30, 30); // đỏ thân
    int armorColor = COLOR(80, 80, 90); // giáp xám
    int eyeColor   = COLOR(255, 220, 0); // mắt vàng
    int legColor   = COLOR(50, 50, 60); // chân đen
    int hornColor  = COLOR(200, 60, 0); // sừng cam

    int headH  = e.height * 2 / 5;
    int bodyH  = e.height * 2 / 5;
    int bodyTop= y2 - e.height / 5 - bodyH;
    int headBot= bodyTop;
    int headTop= headBot - headH;

    // thân
    setfillstyle(SOLID_FILL, armorColor);
    bar(x1 + 4, bodyTop, x2 - 4, y2 - e.height / 5);

    // chân
    setfillstyle(SOLID_FILL, legColor);
    bar(x1 + 4, y2 - e.height / 5, x2 - 4, y2 - 3);

    // đầu
    setfillstyle(SOLID_FILL, bodyColor);
    bar(x1 + 5, headTop + 2, x2 - 5, headBot - 1);

    // sừng
    setcolor(HEX2COLOR(0xCC3300));
    setfillstyle(SOLID_FILL, hornColor);
    int hx = e.facingRight ? (x2 - 7) : (x1 + 7);
    int pts[8] = { hx - 4, headTop + 4, hx + 4, headTop + 4,
                   hx,     headTop - 6, hx - 4, headTop + 4 };
    fillpoly(4, pts);

    // mắt sáng
    setfillstyle(SOLID_FILL, eyeColor);
    int eyeY = headTop + headH / 2;
    if (e.facingRight) {
        bar(x2 - 9, eyeY - 2, x2 - 5, eyeY + 2);
    } else {
        bar(x1 + 5, eyeY - 2, x1 + 9, eyeY + 2);
    }

    // viền
    setcolor(COLOR(20, 0, 0));
    rectangle(x1 + 3, headTop, x2 - 3, y2);

    // vũ khí
    setcolor(COLOR(180, 180, 200));
    setlinestyle(SOLID_LINE, 0, 2);
    if (e.facingRight) {
        line(x2 - 4, bodyTop + 4, x2 + 10, bodyTop + 10);
    } else {
        line(x1 + 4, bodyTop + 4, x1 - 10, bodyTop + 10);
    }
    setlinestyle(SOLID_LINE, 0, 1);
}

// vẽ đạn
static void drawBullet(const Bullet& b) {
    if (!b.active) return;
    int bx = static_cast<int>(b.x);
    int by = static_cast<int>(b.y);
    drawCustomBullet(bx, by, false);
    return;

    // nhân đạn phát sáng
    setfillstyle(SOLID_FILL, COLOR(255, 80, 0));
    fillellipse(bx, by, BULLET_RADIUS + 2, BULLET_RADIUS + 2);
    setfillstyle(SOLID_FILL, COLOR(255, 220, 100));
    fillellipse(bx, by, BULLET_RADIUS - 1, BULLET_RADIUS - 1);
}

// update enemy
static void updateEnemy(Enemy& e, Bullet bullets[], int numBullets, 
                       const Player& player,
                       bool (*isSolidTile)(int row, int col)) {
    if (!e.active) return;
    
  // ====== VA CHẠM VỚI MAP
    // trọng lực
    e.vy += GAME_GRAVITY * GAME_SPEED_MULTIPLIER;
    if (e.vy > GAME_MAX_FALL_SPEED) e.vy = GAME_MAX_FALL_SPEED;
    
    int halfW = e.width / 2;
    int fullH = e.height;
    
    // va chạm trục Y
    float newYf = e.y + e.vy * GAME_SPEED_MULTIPLIER;
    int leftX = e.x - halfW;
    int rightX = e.x + halfW - 1;
    e.onGround = false;
    
    if (e.vy > 0.0f) { // rơi xuống
        int bottom = static_cast<int>(newYf);
        int row = bottom / TILE_SIZE;
        int colStart = leftX / TILE_SIZE;
        int colEnd = rightX / TILE_SIZE;
        bool hit = false;
        for (int c = colStart; c <= colEnd; ++c) {
            if (isSolidTile(row, c)) { hit = true; break; }
        }
        if (hit) {
            newYf = row * TILE_SIZE;
            e.vy = 0.0f;
            e.onGround = true;
        }
    } else if (e.vy < 0.0f) { // nhảy lên
        int top = static_cast<int>(newYf) - fullH;
        int row = top / TILE_SIZE;
        int colStart = leftX / TILE_SIZE;
        int colEnd = rightX / TILE_SIZE;
        bool hit = false;
        for (int c = colStart; c <= colEnd; ++c) {
            if (isSolidTile(row, c)) { hit = true; break; }
        }
        if (hit) {
            newYf = (row + 1) * TILE_SIZE + fullH;
            e.vy = 0.0f;
        }
    }
    e.y = static_cast<int>(newYf);
    
  // ====== DI CHUYỂN NGANG
    if (e.canMove && e.onGround) { // chỉ di chuyển khi đứng trên đất
        float newXf = e.x + e.vx * GAME_SPEED_MULTIPLIER;
        int topY = e.y - fullH;
        int bottomY = e.y - 1;
        
        // kiểm tra va chạm tường
        bool hitWall = false;
        if (e.vx > 0.0f) {
            int right = static_cast<int>(newXf) + halfW;
            int col = right / TILE_SIZE;
            for (int r = topY / TILE_SIZE; r <= bottomY / TILE_SIZE; ++r) {
                if (isSolidTile(r, col)) { hitWall = true; break; }
            }
        } else if (e.vx < 0.0f) {
            int left = static_cast<int>(newXf) - halfW;
            int col = left / TILE_SIZE;
            for (int r = topY / TILE_SIZE; r <= bottomY / TILE_SIZE; ++r) {
                if (isSolidTile(r, col)) { hitWall = true; break; }
            }
        }
        
        // kiểm tra biên màn hình
        if (newXf < halfW || newXf > SCREEN_WIDTH - halfW) {
            hitWall = true;
        }
        
        // kiểm tra phạm vi di chuyển
        if (newXf > e.startX + e.moveRange || newXf < e.startX - e.moveRange) {
            hitWall = true;
        }
        
        // đảo chiều nếu va chạm
        if (hitWall) {
            e.vx = -e.vx;
            e.facingRight = (e.vx > 0);
        } else {
            e.x = static_cast<int>(newXf);
        }
    }
    
  // ====== BẮN ĐẠN CHÉO THEO HƯỚNG PLAYER ======
    if (GAME_SPEED_MULTIPLIER <= 0.0f) return;
    e.shootTimer -= (GAME_SPEED_MULTIPLIER >= 1.5f) ? 2 : 1;
    if (e.shootTimer <= 0) {
        e.shootTimer = e.shootCooldown;

        // tính hướng từ enemy đến player
        int originX = e.x;
        int originY = e.y - e.height / 2;
        int targetX = player.x;
        int targetY = player.y - player.height / 2;
        
        float dx = (float)(targetX - originX);
        float dy = (float)(targetY - originY);
        float len = sqrtf(dx * dx + dy * dy);
        if (len < 1.0f) len = 1.0f;
        dx /= len;
        dy /= len;
        
        // cập nhật hướng nhìn enemy
        e.facingRight = (targetX >= originX);

        // tìm slot đạn rảnh và bắn theo hướng player
        for (int i = 0; i < numBullets; ++i) {
            if (!bullets[i].active) {
                bullets[i].active = true;
                bullets[i].x = static_cast<float>(originX);
                bullets[i].y = static_cast<float>(originY);
                bullets[i].vx = dx * BULLET_SPEED;
                bullets[i].vy = dy * BULLET_SPEED;
                bullets[i].isRocket = false;
                break;
            }
        }
    }
}

// update đạn
static void updateBullet(Bullet& b) {
    if (!b.active) return;
    b.x += b.vx * GAME_SPEED_MULTIPLIER;
    b.y += b.vy * GAME_SPEED_MULTIPLIER;

    // ra ngoài màn hình
    if (b.x < 0 || b.x > SCREEN_WIDTH || b.y < 0 || b.y > SCREEN_HEIGHT) {
        b.active = false;
    }
}

// va chạm đạn với map tile rắn
static bool bulletHitsSolidTile(const Bullet& b, bool (*isSolidTile)(int row, int col)) {
    if (!b.active || isSolidTile == NULL) return false;

    int bx = static_cast<int>(b.x);
    int by = static_cast<int>(b.y);
    int r = BULLET_RADIUS;

    int left   = (bx - r) / TILE_SIZE;
    int right  = (bx + r) / TILE_SIZE;
    int top    = (by - r) / TILE_SIZE;
    int bottom = (by + r) / TILE_SIZE;

    for (int row = top; row <= bottom; ++row) {
        for (int col = left; col <= right; ++col) {
            if (isSolidTile(row, col)) return true;
        }
    }

    return false;
}

static void updateBulletWithTileCollision(Bullet& b, bool (*isSolidTile)(int row, int col)) {
    if (!b.active) return;

    b.x += b.vx * GAME_SPEED_MULTIPLIER;
    b.y += b.vy * GAME_SPEED_MULTIPLIER;

    if (b.x < 0 || b.x > SCREEN_WIDTH || b.y < 0 || b.y > SCREEN_HEIGHT) {
        b.active = false;
        return;
    }

    if (bulletHitsSolidTile(b, isSolidTile)) {
        b.active = false;
    }
}

// kiểm tra đạn có trúng player không
static bool bulletHitsPlayer(const Bullet& b, int px1, int py1, int px2, int py2) {
    if (!b.active) return false;
    int bx = static_cast<int>(b.x);
    int by = static_cast<int>(b.y);
    return !(bx + BULLET_RADIUS < px1 || bx - BULLET_RADIUS > px2 ||
             by + BULLET_RADIUS < py1 || by - BULLET_RADIUS > py2);
}

// vẽ đạn của Player
static void drawPlayerBullet(const Bullet& b) {
    if (!b.active) return;
    int bx = static_cast<int>(b.x);
    int by = static_cast<int>(b.y);
    if (b.isRocket) {
        // rocket bullet
        midpointCircle(bx, by, 5, COLOR(255, 165, 0)); // Màu cam chuẩn
        filledMidpointCircle(bx, by, 4, COLOR(255, 180, 50)); // Màu cam sáng bên trong
        return;
    }
    drawCustomBullet(bx, by, true);
    return;
    // lớp ngoài xanh biển
    setfillstyle(SOLID_FILL, COLOR(0, 150, 255));
    fillellipse(bx, by, BULLET_RADIUS + 2, BULLET_RADIUS + 2);
    // lớp trong trắng sáng
    setfillstyle(SOLID_FILL, COLOR(200, 240, 255));
    fillellipse(bx, by, BULLET_RADIUS - 1, BULLET_RADIUS - 1);
}

// kiểm tra đạn player có trúng enemy không
static bool playerBulletHitsEnemy(const Bullet& b, const Enemy& e) {
    if (!b.active || !e.active) return false;
    int bx = static_cast<int>(b.x);
    int by = static_cast<int>(b.y);
    int ex1 = e.x - e.width / 2, ex2 = e.x + e.width / 2;
    int ey1 = e.y - e.height,    ey2 = e.y;
    return !(bx + BULLET_RADIUS < ex1 || bx - BULLET_RADIUS > ex2 ||
             by + BULLET_RADIUS < ey1 || by - BULLET_RADIUS > ey2);
}

// helper
struct MouseDir {
    float dx, dy; // vector đơn vị hướng player
    int   mouseX, mouseY; // tọa độ chuột trong cửa sổ game
};

static MouseDir getMouseDirection(int originX, int originY) {
    POINT pt;
    GetCursorPos(&pt);
    // tìm cửa sổ game theo tiêu đề
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

// reset toàn bộ mảng đạn
static void resetBullets(Bullet bullets[], int numBullets) {
    for (int i = 0; i < numBullets; ++i) {
        bullets[i].active = false;
        bullets[i].isRocket = false;
    }
}

#endif // eNTITY_ENEMY_H
