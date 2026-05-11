#ifndef SHOOTING_SYSTEM_H
#define SHOOTING_SYSTEM_H

#include <windows.h>
#include "../config.h"
#include "../entities/Player.h"
#include "../entities/Enemy.h"

// ============================================================
//  Hệ thống bắn đạn chung cho tất cả các level
//  Sử dụng MouseDir và getMouseDirection từ Enemy.h
// ============================================================

// ============================================================
//  Xử lý bắn đạn thường (Click Trái)
// ============================================================
static void handleNormalShoot(Player &player, Bullet playerBullets[], int maxBullets,
                               bool &wasLClick) {
    bool lClick = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    if (lClick && !wasLClick) {
        int originY = player.y - player.height / 2;
        MouseDir md = getMouseDirection(player.x, originY);
        
        // Cập nhật hướng nhìn theo chuột
        player.facingRight = (md.mouseX >= player.x);
        
        // Tìm viên đạn rỗi và bắn
        for (int i = 0; i < maxBullets; ++i) {
            if (!playerBullets[i].active) {
                playerBullets[i].active = true;
                playerBullets[i].x  = (float)player.x;
                playerBullets[i].y  = (float)originY;
                playerBullets[i].vx = md.dx * PLAYER_BULLET_SPEED;
                playerBullets[i].vy = md.dy * PLAYER_BULLET_SPEED;
                break;
            }
        }
    }
    wasLClick = lClick;
}

// ============================================================
//  Xử lý Rocket Jump (Click Phải)
// ============================================================
static void handleRocketJump(Player &player, Bullet playerBullets[], int maxBullets,
                              int &rocketCooldown, bool &wasRClick) {
    bool rClick = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
    if (rClick && !wasRClick && rocketCooldown <= 0) {
        int originY = player.y - player.height / 2;
        MouseDir md = getMouseDirection(player.x, originY);
        
        // Đẩy player NGƯỢC hướng chuột (tăng hệ số để bù cho góc chéo)
        player.vx = -md.dx * GAME_MOVE_SPEED * 2.5f;
        player.vy = -md.dy * GAME_JUMP_VELOCITY * 1.3f;
        player.onGround = false;
        rocketCooldown = ROCKET_COOLDOWN_MAX;
        
        // Cập nhật hướng nhìn
        player.facingRight = (md.mouseX >= player.x);
        
        // Bắn đạn mạnh về hướng chuột
        for (int i = 0; i < maxBullets; ++i) {
            if (!playerBullets[i].active) {
                playerBullets[i].active = true;
                playerBullets[i].x  = (float)player.x;
                playerBullets[i].y  = (float)originY;
                playerBullets[i].vx = md.dx * PLAYER_BULLET_SPEED * 1.5f;
                playerBullets[i].vy = md.dy * PLAYER_BULLET_SPEED * 1.5f;
                break;
            }
        }
    }
    wasRClick = rClick;
}

// ============================================================
//  Cập nhật đạn player và kiểm tra va chạm với enemy
// ============================================================
static void updatePlayerBullets(Bullet playerBullets[], int maxBullets,
                                 Enemy enemies[], int maxEnemies) {
    for (int i = 0; i < maxBullets; ++i) {
        updateBullet(playerBullets[i]);
        if (!playerBullets[i].active) continue;
        
        // Kiểm tra trúng enemy
        for (int j = 0; j < maxEnemies; ++j) {
            if (playerBulletHitsEnemy(playerBullets[i], enemies[j])) {
                enemies[j].active       = false;
                playerBullets[i].active = false;
                break;
            }
        }
    }
}

// ============================================================
//  Vẽ thanh hồi chiêu Rocket Jump
// ============================================================
static void drawRocketCooldownBar(int rocketCooldown, bool paused) {
    if (paused) return;
    
    int barW = 120, barH = 10;
    int barX = SCREEN_WIDTH / 2 - barW / 2;
    int barY = 68;
    int filled = (rocketCooldown <= 0) ? barW
               : barW - barW * rocketCooldown / ROCKET_COOLDOWN_MAX;
    
    drawRect(barX, barY, barW, barH, 0x333333);
    drawRect(barX, barY, filled, barH, rocketCooldown <= 0 ? 0x00AAFF : 0x005588);
    
    setcolor(HEX2COLOR(0xAAAAAA));
    setbkcolor(HEX2COLOR(0x333333));
    settextstyle(10, HORIZ_DIR, 1);
    char rLabel[] = "ROCKET";
    outtextxy(barX + barW / 2 - textwidth(rLabel) / 2, barY + 1, rLabel);
    setbkcolor(HEX2COLOR(GAME_COLOR_BG));
}

// ============================================================
//  Kiểm tra đạn quái trúng player và xử lý HP
//  Trả về true nếu player chết (hết HP)
// ============================================================
static bool checkEnemyBulletsHitPlayer(Bullet bullets[], int maxBullets, Player &player) {
    if (player.invincibleTimer > 0) {
        player.invincibleTimer--;
        return false; // Đang bất tử, không nhận sát thương
    }
    
    int px1 = player.x - player.width / 2;
    int px2 = player.x + player.width / 2;
    int py1 = player.y - player.height;
    int py2 = player.y;
    
    for (int i = 0; i < maxBullets; ++i) {
        if (bulletHitsPlayer(bullets[i], px1, py1, px2, py2)) {
            player.hp--;
            bullets[i].active = false;
            player.invincibleTimer = 60; // 1 giây bất tử (60 frames)
            
            if (player.hp <= 0) {
                return true; // Player chết
            }
            break; // Chỉ nhận 1 đạn mỗi lần
        }
    }
    
    return false;
}

#endif // SHOOTING_SYSTEM_H
