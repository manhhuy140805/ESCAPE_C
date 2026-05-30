#ifndef LEVEL4_GAMEPLAY_H
#define LEVEL4_GAMEPLAY_H

#include <graphics.h>
#include <conio.h>
#include <windows.h>

#include "../config.h"
#include "../entities/Player.h"
#include "../entities/Items.h"
#include "../map/Level4.h"
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

// forward declaration Level5
static void runGameLevel5();

static bool isSolidTileLevel4(int row, int col) {
    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS) return false;
    int t = LEVEL4_MAP[row][col];
    return (t == 1 || t == 2 || t == 4);
}

static void initLevel4() {
    int startCol = 1;
    int startRow = 22;
    player = makeDefaultPlayer(startCol * TILE_SIZE + TILE_SIZE / 2, startRow * TILE_SIZE);

    int doorRow = -1, doorCol = -1;
    for (int r = 0; r < MAP_ROWS; ++r) {
        for (int c = 0; c < MAP_COLS; ++c) {
            if (LEVEL4_MAP[r][c] == 2) { doorRow = r; doorCol = c; break; }
        }
        if (doorRow != -1) break;
    }
    if (doorRow == -1) { doorRow = 3; doorCol = 36; }

    door1.x = doorCol * TILE_SIZE + TILE_SIZE / 2;
    door1.y = doorRow * TILE_SIZE;
    door1.open = false;

    keysCollected = 0;
    int found = 0;
    for (int r = MAP_ROWS - 1; r >= 0 && found < GAME_KEYS_REQUIRED; --r) {
        for (int c = 0; c < MAP_COLS && found < GAME_KEYS_REQUIRED; ++c) {
            if (LEVEL4_MAP[r][c] == 2) {
                if (r == doorRow && c == doorCol) continue;
                keys[found].x = c * TILE_SIZE + TILE_SIZE / 2;
                keys[found].y = r * TILE_SIZE;
                keys[found].collected = false;
                ++found;
            }
        }
    }

    // khởi tạo enemies Level 4
    enemies[0] = makeEnemy(13 * TILE_SIZE, 20 * TILE_SIZE, false, 85, true, 45);
    enemies[1] = makeEnemy(16 * TILE_SIZE, 18 * TILE_SIZE, true, 95, false, 0);
    enemies[2] = makeEnemy(34 * TILE_SIZE, 14 * TILE_SIZE, false, 105, true, 35);
    for (int i = 3; i < MAX_ENEMIES; ++i) enemies[i].active = false;
    resetBullets(bullets, MAX_BULLETS);
    resetBullets(playerBullets, MAX_PLAYER_BULLETS);
    rocketCooldown = 0;
}

static void runGameLevel4() {
    initLevel4();
    bool running = true;
    bool wasJumpDown = false;
    bool wasLClick = false;
    bool wasRClick = false;
    bool paused = false;
    bool wasPauseDown = false;
    MovementControl movementControl;

    while (currentState == PLAYING && running) {
        bool playerDead = false;
        bool reachedDoor = false;

        SHORT pDown = GetAsyncKeyState('P');
        bool pauseDown = (pDown & 0x8000) != 0;
        if (pauseDown && !wasPauseDown) paused = !paused;
        wasPauseDown = pauseDown;

        if (!paused) {
            handleSpeedControlKeys();
            SHORT wDown = GetAsyncKeyState('W');
            SHORT spaceDown = GetAsyncKeyState(VK_SPACE);

            updatePlayerHorizontalMovement(player, movementControl);

            bool jumpDown = ((wDown & 0x8000) != 0) || ((spaceDown & 0x8000) != 0);
            if (jumpDown && !wasJumpDown && player.onGround) { player.vy = -GAME_JUMP_VELOCITY; player.onGround = false; }
            wasJumpDown = jumpDown;

            player.vy += GAME_GRAVITY * GAME_SPEED_MULTIPLIER;
            if (player.vy > GAME_MAX_FALL_SPEED) player.vy = GAME_MAX_FALL_SPEED;

            int halfW = player.width / 2, fullH = player.height;

            float newXf = player.x + player.vx * GAME_SPEED_MULTIPLIER;
            int topY = player.y - fullH, bottomY = player.y - 1;
            if (player.vx > 0.0f) {
                int col = (static_cast<int>(newXf) + halfW) / TILE_SIZE;
                bool hit = false;
                for (int r = topY / TILE_SIZE; r <= bottomY / TILE_SIZE; ++r)
                    if (isSolidTileLevel4(r, col)) { hit = true; break; }
                if (hit) { newXf = col * TILE_SIZE - halfW - 1; player.vx = 0.0f; }
            } else if (player.vx < 0.0f) {
                int col = (static_cast<int>(newXf) - halfW) / TILE_SIZE;
                bool hit = false;
                for (int r = topY / TILE_SIZE; r <= bottomY / TILE_SIZE; ++r)
                    if (isSolidTileLevel4(r, col)) { hit = true; break; }
                if (hit) { newXf = (col + 1) * TILE_SIZE + halfW + 1; player.vx = 0.0f; }
            }
            player.x = static_cast<int>(newXf);
            if (player.x < halfW) player.x = halfW;
            if (player.x > SCREEN_WIDTH - halfW) player.x = SCREEN_WIDTH - halfW;

            float newYf = player.y + player.vy * GAME_SPEED_MULTIPLIER;
            int leftX = player.x - halfW, rightX = player.x + halfW - 1;
            player.onGround = false;
            if (player.vy > 0.0f) {
                int row = static_cast<int>(newYf) / TILE_SIZE;
                bool hit = false;
                for (int c = leftX / TILE_SIZE; c <= rightX / TILE_SIZE; ++c)
                    if (isSolidTileLevel4(row, c)) { hit = true; break; }
                if (hit) { newYf = row * TILE_SIZE; player.vy = 0.0f; player.onGround = true; }
            } else if (player.vy < 0.0f) {
                int row = (static_cast<int>(newYf) - fullH) / TILE_SIZE;
                bool hit = false;
                for (int c = leftX / TILE_SIZE; c <= rightX / TILE_SIZE; ++c)
                    if (isSolidTileLevel4(row, c)) { hit = true; break; }
                if (hit) { newYf = (row + 1) * TILE_SIZE + fullH; player.vy = 0.0f; }
            }
            player.y = static_cast<int>(newYf);

            int px1 = player.x - player.width / 2, px2 = player.x + player.width / 2;
            int py1 = player.y - player.height,    py2 = player.y;

            for (int r = py1 / TILE_SIZE; r <= py2 / TILE_SIZE && !playerDead; ++r)
                for (int c = px1 / TILE_SIZE; c <= px2 / TILE_SIZE && !playerDead; ++c) {
                    if (r < 0 || r >= MAP_ROWS || c < 0 || c >= MAP_COLS) continue;
                    int t = LEVEL4_MAP[r][c];
                    if (t == 3 || t == 4) playerDead = true;
                }

            if (playerDead) {
                EndAction action = showEndScreen(4, false);
                if (action == END_RESTART) { initLevel4(); wasJumpDown = false; continue; }
                currentState = MENU; running = false; break;
            }

  // ====== Cập nhật enemy và đạn
            for (int i = 0; i < MAX_ENEMIES; ++i)
                updateEnemy(enemies[i], bullets, MAX_BULLETS, player, isSolidTileLevel4);
            for (int i = 0; i < MAX_BULLETS; ++i)
                updateBulletWithTileCollision(bullets[i], isSolidTileLevel4);

            // kiểm tra đạn quái trúng player
            if (checkEnemyBulletsHitPlayer(bullets, MAX_BULLETS, player)) {
                playerDead = true;
            }

            // nếu hết HP
            if (playerDead) {
                EndAction action = showEndScreen(4, false);
                if (action == END_RESTART) { initLevel4(); wasJumpDown = false; continue; }
                currentState = MENU; running = false; break;
            }

  // ====== Bắn đạn
            handleNormalShoot(player, playerBullets, MAX_PLAYER_BULLETS, wasLClick);
            handleRocketJump(player, playerBullets, MAX_PLAYER_BULLETS, rocketCooldown, wasRClick);
            if (rocketCooldown > 0) rocketCooldown--;
            updatePlayerBullets(playerBullets, MAX_PLAYER_BULLETS, enemies, MAX_ENEMIES, isSolidTileLevel4);

            for (int i = 0; i < GAME_KEYS_REQUIRED; ++i) {
                if (keys[i].collected) continue;
                bool overlap = !(px2 < keys[i].x - TILE_SIZE/2 || px1 > keys[i].x + TILE_SIZE/2 ||
                                 py2 < keys[i].y - TILE_SIZE    || py1 > keys[i].y);
                if (overlap) { keys[i].collected = true; keysCollected++; playCollectSound(); }
            }
            if (!door1.open && keysCollected >= GAME_KEYS_REQUIRED) { door1.open = true; playDoorSound(); }

            if (door1.open) {
                reachedDoor = !(px2 < door1.x - TILE_SIZE || px1 > door1.x + TILE_SIZE ||
                                py2 < door1.y - TILE_SIZE * 2 || py1 > door1.y);
            }
            if (reachedDoor) {
                EndAction action = showEndScreen(4, true);
                if (action == END_RESTART) { initLevel4(); wasJumpDown = false; continue; }
                else if (action == END_NEXT) { runGameLevel5(); currentState = MENU; running = false; break; }
                currentState = MENU; running = false; break;
            }
        }

        beginFrame();
        
        // background Level 4
        drawLevel4Background();
        drawStars();
        
        drawLevel4();
        for (int i = 0; i < GAME_KEYS_REQUIRED; ++i) drawKey(keys[i]);
        drawDoor(door1);
        for (int i = 0; i < MAX_ENEMIES; ++i)       drawEnemy(enemies[i]);
        for (int i = 0; i < MAX_BULLETS; ++i)        drawBullet(bullets[i]);
        for (int i = 0; i < MAX_PLAYER_BULLETS; ++i) drawPlayerBullet(playerBullets[i]);
        drawPlayer(player);
        drawPlayerHP(player);
        drawLevelHUD(4, keysCollected, GAME_KEYS_REQUIRED, paused);
        drawRocketCooldownBar(rocketCooldown, paused);

        if (kbhit()) { char key = getch(); if (key == 27) { currentState = MENU; running = false; } }

        endFrame();
        delay(FRAME_DELAY);
    }
}

#endif // lEVEL4_GAMEPLAY_H
