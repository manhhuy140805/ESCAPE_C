#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include "config.h"
#include "graphics/Menu.h"
#include "entities/Player.h"
#include "entities/Items.h"
#include "entities/Enemy.h"
#include "core/doublebuffer.h"
#include "core/blocks.h"
#include "core/sound.h"
#include "levels/Level1.h"
#include "levels/Level2.h"
#include "levels/Level3.h"
#include "levels/Level4.h"
#include "levels/Level5.h"

GameState currentState = MENU;
bool showInstructions = false;
bool showLevelSelect = false;
int selectedLevel = 1;
float GAME_SPEED_MULTIPLIER = 1.0f;
int GAME_SPEED_MODE = 2;

Player player;
KeyItem keys[GAME_KEYS_REQUIRED];
DoorItem door1;
int keysCollected = 0;

Enemy  enemies[MAX_ENEMIES];
Bullet bullets[MAX_BULLETS];
Bullet playerBullets[MAX_PLAYER_BULLETS];
int    rocketCooldown = 0;

void initGraphics() {
    int gd = DETECT, gm;
    char empty[] = "";
    initgraph(&gd, &gm, empty);
    initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Parkour 2D - Me Cung Phieu Luu");

    // khởi tạo page ban đầu
    setactivepage(0);
    setvisualpage(0);

    setbkcolor(GAME_COLOR_BG);
    cleardevice();
}

// initLevel1 và runGameLevel1 đã được tách sang levels/Level1.h

static void drawLevelSelectScreen() {
    drawLabyrinthBackground();
    drawStars();

    settextstyle(10, HORIZ_DIR, 5);
    char title[] = "SELECT LEVEL";
    setcolor(0);
    outtextxy(SCREEN_WIDTH / 2 - textwidth(title) / 2 + 3, 83, title);
    setcolor(14);
    outtextxy(SCREEN_WIDTH / 2 - textwidth(title) / 2, 80, title);

    int centerX = SCREEN_WIDTH / 2;
    int startY = 210;
    int spacing = 82;
    int btnW = 430;
    int btnH = 58;

    char level1[] = "LEVEL 1 - START";
    char level2[] = "LEVEL 2 - CAVE";
    char level3[] = "LEVEL 3 - DESERT";
    char level4[] = "LEVEL 4 - SNOW";
    char level5[] = "LEVEL 5 - FINAL";
    char* labels[5] = { level1, level2, level3, level4, level5 };

    for (int i = 0; i < 5; ++i) {
        drawGameButton(centerX, startY + i * spacing, btnW, btnH, labels[i], selectedLevel == i + 1);
    }

    settextstyle(8, HORIZ_DIR, 2);
    setcolor(15);
    char hint[] = "UP/DOWN or 1-5: Select  |  ENTER: Play  |  ESC: Back";
    outtextxy(SCREEN_WIDTH / 2 - textwidth(hint) / 2, 690, hint);
}

static void runSelectedLevel() {
    if (selectedLevel == 1) runGameLevel1();
    else if (selectedLevel == 2) runGameLevel2();
    else if (selectedLevel == 3) runGameLevel3();
    else if (selectedLevel == 4) runGameLevel4();
    else runGameLevel5();
}

void runMenu(Menu& menu) {
    while (currentState == MENU) {
        beginFrame();
        if (showInstructions) {
            // hiển thị màn hình hướng dẫn
            menu.drawInstructions();
            
            // chờ ESC để quay lại menu
            if (kbhit()) {
                char key = getch();
                if (key == 27) { // eSC
                    showInstructions = false;
                }
            }
        } else if (showLevelSelect) {
            drawLevelSelectScreen();

            if (kbhit()) {
                char key = getch();
                if (key == 27) {
                    showLevelSelect = false;
                } else if (key >= '1' && key <= '5') {
                    selectedLevel = key - '0';
                } else if (key == 13 || key == '\r' || key == '\n') {
                    currentState = PLAYING;
                    endFrame();
                    return;
                } else if (key == 0 || key == -32) {
                    key = getch();
                    if (key == 72) {
                        selectedLevel--;
                        if (selectedLevel < 1) selectedLevel = 5;
                    } else if (key == 80) {
                        selectedLevel++;
                        if (selectedLevel > 5) selectedLevel = 1;
                    }
                }
            }
        } else {
            // hiển thị menu chính
            menu.draw();
            
            // kiểm tra input
            if (kbhit()) {
                char key = getch();
                
                if (key == 13 || key == '\r' || key == '\n') { // eNTER
                    int option = menu.getSelectedOption();
                    if (option == 0) {
                        showLevelSelect = true;
                    } else if (option == 1) {
                        showInstructions = true; // xem hướng dẫn
                    } else if (option == 2) {
                        closegraph(); // thoát
                        exit(0);
                    }
                } else if (key == 0 || key == -32) { // extended key
                    key = getch();
                    if (key == 72 || key == 80) { // uP or DOWN
                        menu.setLastKey(key);
                        menu.handleInput();
                    }
                }
            }
        }
        
        endFrame();
        delay(50); // giảm CPU usage
    }
}

int main() {
    initGraphics();
    playBackgroundMusic("src/medias/nhacNen.mp3");

    Menu menu;

    // vòng đời game
    while (true) {
        currentState = MENU;
        runMenu(menu);

        if (currentState == PLAYING) {
            runSelectedLevel();
            // sau khi chơi xong
            continue;
        }

        // nếu runMenu thoát mà không chuyển sang PLAYING
        break;
    }

    closegraph();
    stopBackgroundMusic();
    return 0;
}
