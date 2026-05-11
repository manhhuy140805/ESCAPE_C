#ifndef LEVEL3_GAMEPLAY_H
#define LEVEL3_GAMEPLAY_H

#include <graphics.h>
#include <conio.h>
#include <windows.h>

#include "../config.h"
#include "../entities/Player.h"
#include "../entities/Items.h"
#include "../map/Level3.h"
#include "../core/doublebuffer.h"
#include "../core/decorations.h"
#include "../core/blocks.h"
#include "../utils/ShootingSystem.h"
#include "LevelCommon.h"

extern GameState currentState;
extern Player player;
extern KeyItem keys[GAME_KEYS_REQUIRED];
extern DoorItem door1;
extern int keysCollected;
extern Enemy  enemies[MAX_ENEMIES];
extern Bullet bullets[MAX_BULLETS];
extern Bullet playerBullets[MAX_PLAYER_BULLETS];
extern int    rocketCooldown;

// Forward declaration Level4
static void runGameLevel4();

static bool isSolidTileLevel3(int row, int col) {
    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS) return false;
    int t = LEVEL3_MAP[row][col];
    return (t == 1 || t == 2 || t == 4);
}

static void initLevel3() {
    int startCol = 1;
    int startRow = 22;
    player = makeDefaultPlayer(startCol * TILE_SIZE + TILE_SIZE / 2, startRow * TILE_SIZE);

    // Cửa: block cỏ CAO NHẤT
    int doorRow = -1, doorCol = -1;
    for (int r = 0; r < MAP_ROWS; ++r) {
        for (int c = 0; c < MAP_COLS; ++c) {
            if (LEVEL3_MAP[r][c] == 2) { doorRow = r; doorCol = c; break; }
        }
        if (doorRow != -1) break;
    }
    if (doorRow == -1) { doorRow = 5; doorCol = 26; }

    door1.x = doorCol * TILE_SIZE + TILE_SIZE / 2;
    door1.y = doorRow * TILE_SIZE;
    door1.open = false;

    // Chìa khóa: block cỏ từ THẤP lên CAO
    keysCollected = 0;
    int found = 0;
    for (int r = MAP_ROWS - 1; r >= 0 && found < GAME_KEYS_REQUIRED; --r) {
        for (int c = 0; c < MAP_COLS && found < GAME_KEYS_REQUIRED; ++c) {
            if (LEVEL3_MAP[r][c] == 2) {
                if (r == doorRow && c == doorCol) continue;
                keys[found].x = c * TILE_SIZE + TILE_SIZE / 2;
                keys[found].y = r * TILE_SIZE;
                keys[found].collected = false;
                ++found;
            }
        }
    }

    // Khởi tạo enemies Level 3
    enemies[0] = makeEnemy(15 * TILE_SIZE, 18 * TILE_SIZE, false, 90, true, 70);
    enemies[1] = makeEnemy(28 * TILE_SIZE, 15 * TILE_SIZE, true, 100, true, 90);
    for (int i = 2; i < MAX_ENEMIES; ++i) enemies[i].active = false;
    resetBullets(bullets, MAX_BULLETS);
    resetBullets(playerBullets, MAX_PLAYER_BULLETS);
    rocketCooldown = 0;
}

static void runGameLevel3() {
    initLevel3();
    bool running = true;
    bool wasJumpDown = false;
    bool wasLClick = false;
    bool wasRClick = false;
    bool paused = false;
    bool wasPauseDown = false;

    while (currentState == PLAYING && running) {
        bool playerDead = false;
        bool reachedDoor = false;

        SHORT pDown = GetAsyncKeyState('P');
        bool pauseDown = (pDown & 0x8000) != 0;
        if (pauseDown && !wasPauseDown) paused = !paused;
        wasPauseDown = pauseDown;

        if (!paused) {
            SHORT aDown = GetAsyncKeyState('A');
            SHORT dDown = GetAsyncKeyState('D');
            SHORT wDown = GetAsyncKeyState('W');
            SHORT spaceDown = GetAsyncKeyState(VK_SPACE);

            if (aDown & 0x8000) { player.vx = -GAME_MOVE_SPEED; player.facingRight = false; }
            else if (dDown & 0x8000) { player.vx = GAME_MOVE_SPEED; player.facingRight = true; }
            else { player.vx *= GAME_FRICTION; if (player.vx > -0.1f && player.vx < 0.1f) player.vx = 0.0f; }

            bool jumpDown = ((wDown & 0x8000) != 0) || ((spaceDown & 0x8000) != 0);
            if (jumpDown && !wasJumpDown && player.onGround) { player.vy = -GAME_JUMP_VELOCITY; player.onGround = false; }
            wasJumpDown = jumpDown;

            player.vy += GAME_GRAVITY;
            if (player.vy > GAME_MAX_FALL_SPEED) player.vy = GAME_MAX_FALL_SPEED;

            int halfW = player.width / 2;
            int fullH = player.height;

            // Va chạm trục X
            float newXf = player.x + player.vx;
            int topY = player.y - fullH, bottomY = player.y - 1;
            if (player.vx > 0.0f) {
                int col = (static_cast<int>(newXf) + halfW) / TILE_SIZE;
                bool hit = false;
                for (int r = topY / TILE_SIZE; r <= bottomY / TILE_SIZE; ++r)
                    if (isSolidTileLevel3(r, col)) { hit = true; break; }
                if (hit) { newXf = col * TILE_SIZE - halfW - 1; player.vx = 0.0f; }
            } else if (player.vx < 0.0f) {
                int col = (static_cast<int>(newXf) - halfW) / TILE_SIZE;
                bool hit = false;
                for (int r = topY / TILE_SIZE; r <= bottomY / TILE_SIZE; ++r)
                    if (isSolidTileLevel3(r, col)) { hit = true; break; }
                if (hit) { newXf = (col + 1) * TILE_SIZE + halfW + 1; player.vx = 0.0f; }
            }
            player.x = static_cast<int>(newXf);
            if (player.x < halfW) player.x = halfW;
            if (player.x > SCREEN_WIDTH - halfW) player.x = SCREEN_WIDTH - halfW;

            // Va chạm trục Y
            float newYf = player.y + player.vy;
            int leftX = player.x - halfW, rightX = player.x + halfW - 1;
            player.onGround = false;
            if (player.vy > 0.0f) {
                int row = static_cast<int>(newYf) / TILE_SIZE;
                bool hit = false;
                for (int c = leftX / TILE_SIZE; c <= rightX / TILE_SIZE; ++c)
                    if (isSolidTileLevel3(row, c)) { hit = true; break; }
                if (hit) { newYf = row * TILE_SIZE; player.vy = 0.0f; player.onGround = true; }
            } else if (player.vy < 0.0f) {
                int row = (static_cast<int>(newYf) - fullH) / TILE_SIZE;
                bool hit = false;
                for (int c = leftX / TILE_SIZE; c <= rightX / TILE_SIZE; ++c)
                    if (isSolidTileLevel3(row, c)) { hit = true; break; }
                if (hit) { newYf = (row + 1) * TILE_SIZE + fullH; player.vy = 0.0f; }
            }
            player.y = static_cast<int>(newYf);

            // AABB
            int px1 = player.x - player.width / 2, px2 = player.x + player.width / 2;
            int py1 = player.y - player.height,    py2 = player.y;

            // Hazard check
            for (int r = py1 / TILE_SIZE; r <= py2 / TILE_SIZE && !playerDead; ++r)
                for (int c = px1 / TILE_SIZE; c <= px2 / TILE_SIZE && !playerDead; ++c) {
                    if (r < 0 || r >= MAP_ROWS || c < 0 || c >= MAP_COLS) continue;
                    int t = LEVEL3_MAP[r][c];
                    if (t == 3 || t == 4) playerDead = true;
                }

            if (playerDead) {
                EndAction action = showEndScreen(3, false);
                if (action == END_RESTART) { initLevel3(); wasJumpDown = false; continue; }
                currentState = MENU; running = false; break;
            }

            // ====== Cập nhật enemy và đạn (quái) ======
            for (int i = 0; i < MAX_ENEMIES; ++i)
                updateEnemy(enemies[i], bullets, MAX_BULLETS);
            for (int i = 0; i < MAX_BULLETS; ++i)
                updateBullet(bullets[i]);

            // Kiểm tra đạn quái trúng player (dùng hệ thống HP)
            if (checkEnemyBulletsHitPlayer(bullets, MAX_BULLETS, player)) {
                playerDead = true;
            }

            // ====== Bắn đạn: Sử dụng hệ thống bắn đạn chung ======
            handleNormalShoot(player, playerBullets, MAX_PLAYER_BULLETS, wasLClick);
            handleRocketJump(player, playerBullets, MAX_PLAYER_BULLETS, rocketCooldown, wasRClick);
            if (rocketCooldown > 0) rocketCooldown--;
            updatePlayerBullets(playerBullets, MAX_PLAYER_BULLETS, enemies, MAX_ENEMIES);

            // Nhặt chìa
            for (int i = 0; i < GAME_KEYS_REQUIRED; ++i) {
                if (keys[i].collected) continue;
                bool overlap = !(px2 < keys[i].x - TILE_SIZE/2 || px1 > keys[i].x + TILE_SIZE/2 ||
                                 py2 < keys[i].y - TILE_SIZE    || py1 > keys[i].y);
                if (overlap) { keys[i].collected = true; keysCollected++; }
            }
            if (!door1.open && keysCollected >= GAME_KEYS_REQUIRED) door1.open = true;

            // Chạm cửa
            if (door1.open) {
                reachedDoor = !(px2 < door1.x - TILE_SIZE || px1 > door1.x + TILE_SIZE ||
                                py2 < door1.y - TILE_SIZE * 3 || py1 > door1.y);
            }
            if (reachedDoor) {
                EndAction action = showEndScreen(3, true);
                if (action == END_RESTART) { initLevel3(); wasJumpDown = false; continue; }
                else if (action == END_NEXT) { runGameLevel4(); currentState = MENU; running = false; break; }
                currentState = MENU; running = false; break;
            }
        }

        beginFrame();
        
        // Background giống menu
        drawLabyrinthBackground();
        drawStars();
        
        drawLevel3();
        for (int i = 0; i < GAME_KEYS_REQUIRED; ++i) drawKey(keys[i]);
        drawDoor(door1);
        for (int i = 0; i < MAX_ENEMIES; ++i)       drawEnemy(enemies[i]);
        for (int i = 0; i < MAX_BULLETS; ++i)        drawBullet(bullets[i]);
        for (int i = 0; i < MAX_PLAYER_BULLETS; ++i) drawPlayerBullet(playerBullets[i]);
        drawPlayer(player);
        drawPlayerHP(player);
        drawLevelHUD(3, keysCollected, GAME_KEYS_REQUIRED, paused);
        drawRocketCooldownBar(rocketCooldown, paused);

        if (kbhit()) { char key = getch(); if (key == 27) { currentState = MENU; running = false; } }

        endFrame();
        delay(FRAME_DELAY);
    }
}

#endif // LEVEL3_GAMEPLAY_H
