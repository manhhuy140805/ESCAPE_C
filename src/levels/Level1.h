#ifndef LEVEL1_GAMEPLAY_H
#define LEVEL1_GAMEPLAY_H

#include <graphics.h>
#include <conio.h>
#include <windows.h>

#include "../config.h"
#include "../entities/Player.h"
#include "../entities/Items.h"
#include "../entities/Enemy.h"
#include "../map/Level1.h"
#include "../core/doublebuffer.h"
#include "../core/decorations.h"
#include "../core/blocks.h"
#include "../utils/ShootingSystem.h"
#include "LevelCommon.h"
#include "Level2.h"

// các biến trạng thái được định nghĩa trong main.cpp
extern GameState currentState;
extern Player player;
extern KeyItem keys[GAME_KEYS_REQUIRED];
extern DoorItem door1;
extern int keysCollected;
extern Enemy  enemies[MAX_ENEMIES];
extern Bullet bullets[MAX_BULLETS];
extern Bullet playerBullets[MAX_PLAYER_BULLETS];
extern int    rocketCooldown;

// hỗ trợ va chạm map tile
static bool isSolidTile(int row, int col) {
    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS) return false;
    int t = LEVEL1_MAP[row][col];
    // đất, cỏ và dung nham đều là mặt đỡ; gai là hazard mỏng
    return (t == 1 || t == 2 || t == 4);
}

// khởi tạo state cho Level 1
static void initLevel1() {
    // vị trí xuất phát
    int startCol = 1;
    int startRow = 23;
    int startX = startCol * TILE_SIZE + TILE_SIZE / 2;
    int startY = startRow * TILE_SIZE; // chân đứng trên mặt block
    player = makeDefaultPlayer(startX, startY);

    // cửa
    int doorRow = -1;
    int doorCol = -1;
    for (int r = 0; r < MAP_ROWS; ++r) {
        for (int c = 0; c < MAP_COLS; ++c) {
            if (LEVEL1_MAP[r][c] == 2) {
                doorRow = r;
                doorCol = c;
                break;
            }
        }
        if (doorRow != -1) break;
    }

    if (doorRow == -1) {
        // fallback
        doorRow = MAP_ROWS - 3;
        doorCol = MAP_COLS - 4;
    }

    door1.x = doorCol * TILE_SIZE + TILE_SIZE / 2;
    door1.y = doorRow * TILE_SIZE; // chân cửa đặt trên mặt block cỏ
    door1.open = false;

    // đặt 3 chìa khóa trên các block cỏ
    keysCollected = 0;
    int foundKeys = 0;
    for (int r = MAP_ROWS - 1; r >= 0 && foundKeys < GAME_KEYS_REQUIRED; --r) {
        for (int c = 0; c < MAP_COLS && foundKeys < GAME_KEYS_REQUIRED; ++c) {
            if (LEVEL1_MAP[r][c] == 2) {
                // bỏ qua ô đang đặt cửa
                if (r == doorRow && c == doorCol) continue;

                int kx = c * TILE_SIZE + TILE_SIZE / 2;
                int ky = r * TILE_SIZE; // chân chìa ngay trên mặt block cỏ
                keys[foundKeys].x = kx;
                keys[foundKeys].y = ky;
                keys[foundKeys].collected = false;
                ++foundKeys;
            }
        }
    }

    // khởi tạo enemies Level 1
    enemies[0] = makeEnemy(25 * TILE_SIZE, 19 * TILE_SIZE, false, 100, false, 0);
    enemies[1] = makeEnemy(35 * TILE_SIZE, 17 * TILE_SIZE, false, 120, true, 50);
    for (int i = 2; i < MAX_ENEMIES; ++i) enemies[i].active = false;
    resetBullets(bullets, MAX_BULLETS);
    resetBullets(playerBullets, MAX_PLAYER_BULLETS);
    rocketCooldown = 0;
}

// vòng chơi của Level 1
static void runGameLevel1() {
    initLevel1();

    bool running      = true;
    bool wasJumpDown  = false;
    bool wasLClick    = false; // click trái
    bool wasRClick    = false; // click phải
    bool paused       = false;
    bool wasPauseDown = false;
    MovementControl movementControl;

    while (currentState == PLAYING && running) {
        bool playerDead = false;
        bool reachedDoor = false;

        // toggle pause với phím P
        SHORT pDown = GetAsyncKeyState('P');
        bool pauseDown = (pDown & 0x8000) != 0;
        if (pauseDown && !wasPauseDown) {
            paused = !paused;
        }
        wasPauseDown = pauseDown;

        if (!paused) {
            handleSpeedControlKeys();
  // ====== Cập nhật input & vật lý đơn giản ======
            SHORT wDown = GetAsyncKeyState('W');
            SHORT spaceDown = GetAsyncKeyState(VK_SPACE);

            // di chuyển ngang
            updatePlayerHorizontalMovement(player, movementControl);

            // nhảy
            bool jumpDown = ((wDown & 0x8000) != 0) || ((spaceDown & 0x8000) != 0);
            if (jumpDown && !wasJumpDown && player.onGround) {
                player.vy = -GAME_JUMP_VELOCITY; // hướng lên
                player.onGround = false;
            }
            wasJumpDown = jumpDown;

            // trọng lực
            player.vy += GAME_GRAVITY * GAME_SPEED_MULTIPLIER;
            if (player.vy > GAME_MAX_FALL_SPEED) player.vy = GAME_MAX_FALL_SPEED;

            int halfW = player.width / 2;
            int fullH = player.height;

  // ====== Va chạm theo trục X ======
            float newXf = player.x + player.vx * GAME_SPEED_MULTIPLIER;
            int topY = player.y - fullH;
            int bottomY = player.y - 1; // bớt 1 pixel cho chắc

            if (player.vx > 0.0f) {
                int right = static_cast<int>(newXf) + halfW;
                int col = right / TILE_SIZE;
                int rowStart = topY / TILE_SIZE;
                int rowEnd = bottomY / TILE_SIZE;
                bool hit = false;
                for (int r = rowStart; r <= rowEnd; ++r) {
                    if (isSolidTile(r, col)) { hit = true; break; }
                }
                if (hit) {
                    newXf = col * TILE_SIZE - halfW - 1;
                    player.vx = 0.0f;
                }
            } else if (player.vx < 0.0f) {
                int left = static_cast<int>(newXf) - halfW;
                int col = left / TILE_SIZE;
                int rowStart = topY / TILE_SIZE;
                int rowEnd = bottomY / TILE_SIZE;
                bool hit = false;
                for (int r = rowStart; r <= rowEnd; ++r) {
                    if (isSolidTile(r, col)) { hit = true; break; }
                }
                if (hit) {
                    newXf = (col + 1) * TILE_SIZE + halfW + 1;
                    player.vx = 0.0f;
                }
            }

            // cập nhật X sau khi xử lý va chạm ngang
            player.x = static_cast<int>(newXf);

            // giữ trong màn hình ngang
            if (player.x < halfW) player.x = halfW;
            if (player.x > SCREEN_WIDTH - halfW) player.x = SCREEN_WIDTH - halfW;

  // ====== Va chạm theo trục Y ======
            float newYf = player.y + player.vy * GAME_SPEED_MULTIPLIER;
            int leftX = player.x - halfW;
            int rightX = player.x + halfW - 1;
            player.onGround = false;

            if (player.vy > 0.0f) { // rơi xuống
                int bottom = static_cast<int>(newYf);
                int row = bottom / TILE_SIZE;
                int colStart = leftX / TILE_SIZE;
                int colEnd = rightX / TILE_SIZE;
                bool hit = false;
                for (int c = colStart; c <= colEnd; ++c) {
                    if (isSolidTile(row, c)) { hit = true; break; }
                }
                if (hit) {
                    newYf = row * TILE_SIZE; // đứng trên mặt block
                    player.vy = 0.0f;
                    player.onGround = true;
                }
            } else if (player.vy < 0.0f) { // nhảy lên, va chạm trần
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
                    player.vy = 0.0f;
                }
            }

            // cập nhật Y sau khi xử lý va chạm dọc
            player.y = static_cast<int>(newYf);

  // ====== AABB nhân vật ======
            int halfW2 = player.width / 2;
            int fullH2 = player.height;
            int px1 = player.x - halfW2;
            int px2 = player.x + halfW2;
            int py1 = player.y - fullH2;
            int py2 = player.y;

  // ====== Va chạm hazard
            int rowStartH = py1 / TILE_SIZE;
            int rowEndH   = py2 / TILE_SIZE;
            int colStartH = px1 / TILE_SIZE;
            int colEndH   = px2 / TILE_SIZE;
            for (int r = rowStartH; r <= rowEndH; ++r) {
                for (int c = colStartH; c <= colEndH; ++c) {
                    if (r < 0 || r >= MAP_ROWS || c < 0 || c >= MAP_COLS) continue;
                    int t = LEVEL1_MAP[r][c];
                    if (t == 3 || t == 4) {
                        playerDead = true;
                        break;
                    }
                }
                if (playerDead) break;
            }

            // nếu đã chết bởi hazard
            if (playerDead) {
                EndAction action = showEndScreen(1, false);
                if (action == END_RESTART) {
                    initLevel1();
                    wasJumpDown = false;
                    continue; // chơi lại Level 1
                } else if (action == END_NEXT) {
                    // cho phép bỏ qua sang Level 2
                    runGameLevel2();
                    currentState = MENU;
                    running = false;
                    break;
                } else {
                    currentState = MENU;
                    running = false;
                    break;
                }
            }

  // ====== Cập nhật enemy và đạn
            for (int i = 0; i < MAX_ENEMIES; ++i)
                updateEnemy(enemies[i], bullets, MAX_BULLETS, player, isSolidTile);
            for (int i = 0; i < MAX_BULLETS; ++i)
                updateBulletWithTileCollision(bullets[i], isSolidTile);

            // kiểm tra đạn quái trúng player
            if (checkEnemyBulletsHitPlayer(bullets, MAX_BULLETS, player)) {
                playerDead = true;
            }

            // nếu hết HP
            if (playerDead) {
                EndAction action = showEndScreen(1, false);
                if (action == END_RESTART) {
                    initLevel1();
                    wasJumpDown = false;
                    continue;
                } else if (action == END_NEXT) {
                    runGameLevel2();
                    currentState = MENU;
                    running = false;
                    break;
                } else {
                    currentState = MENU;
                    running = false;
                    break;
                }
            }

  // ====== Bắn đạn
            handleNormalShoot(player, playerBullets, MAX_PLAYER_BULLETS, wasLClick);
            handleRocketJump(player, playerBullets, MAX_PLAYER_BULLETS, rocketCooldown, wasRClick);
            if (rocketCooldown > 0) rocketCooldown--;
            updatePlayerBullets(playerBullets, MAX_PLAYER_BULLETS, enemies, MAX_ENEMIES, isSolidTile);


  // ====== Nhặt chìa khóa ======
            for (int i = 0; i < GAME_KEYS_REQUIRED; ++i) {
                if (keys[i].collected) continue;
                int kx1 = keys[i].x - TILE_SIZE / 2;
                int kx2 = keys[i].x + TILE_SIZE / 2;
                int ky1 = keys[i].y - TILE_SIZE;
                int ky2 = keys[i].y;
                bool overlap = !(px2 < kx1 || px1 > kx2 || py2 < ky1 || py1 > ky2);
                if (overlap) {
                    keys[i].collected = true;
                    keysCollected++;
                    playCollectSound();
                }
            }

            // mở cửa khi đủ chìa
            if (!door1.open && keysCollected >= GAME_KEYS_REQUIRED) {
                door1.open = true;
                playDoorSound();
            }

            // kiểm tra thắng
            if (door1.open) {
                int dx1 = door1.x - TILE_SIZE;
                int dx2 = door1.x + TILE_SIZE;
                int dy1 = door1.y - TILE_SIZE * 3;
                int dy2 = door1.y;
                reachedDoor = !(px2 < dx1 || px1 > dx2 || py2 < dy1 || py1 > dy2);
            }

            if (reachedDoor) {
                EndAction action = showEndScreen(1, true);
                if (action == END_RESTART) {
                    initLevel1();
                    wasJumpDown = false;
                    continue; // chơi lại Level 1
                } else if (action == END_NEXT) {
                    // thắng Level 1
                    runGameLevel2();
                    currentState = MENU;
                    running = false;
                    break;
                } else {
                    currentState = MENU;
                    running = false;
                    break;
                }
            }
        }

  // ====== Vẽ frame ======
        beginFrame();

        // background Level 1
        drawLevel1Background();
        drawStars();

        drawLevel1();
        for (int i = 0; i < GAME_KEYS_REQUIRED; ++i) drawKey(keys[i]);
        drawDoor(door1);
        for (int i = 0; i < MAX_ENEMIES; ++i)       drawEnemy(enemies[i]);
        for (int i = 0; i < MAX_BULLETS; ++i)        drawBullet(bullets[i]);
        for (int i = 0; i < MAX_PLAYER_BULLETS; ++i) drawPlayerBullet(playerBullets[i]);
        drawPlayer(player);
        drawPlayerHP(player);

        // hUD chung cho các level
        drawLevelHUD(1, keysCollected, GAME_KEYS_REQUIRED, paused);
        drawRocketCooldownBar(rocketCooldown, paused);

        // eSC
        if (kbhit()) {
            char key = getch();
            if (key == 27) {
                currentState = MENU;
                running = false;
            }
        }

        endFrame();
        delay(FRAME_DELAY);
    }
}

#endif // lEVEL1_GAMEPLAY_H
