#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include "config.h"
#include "graphics/Menu.h"
#include "entities/Player.h"
#include "entities/Items.h"
#include "entities/Enemy.h"
#include "core/doublebuffer.h"
#include "levels/Level1.h"
#include "levels/Level2.h"
#include "levels/Level3.h"
#include "levels/Level4.h"
#include "levels/Level5.h"

GameState currentState = MENU;
bool showInstructions = false;

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

    // Khởi tạo page ban đầu
    setactivepage(0);
    setvisualpage(0);

    setbkcolor(GAME_COLOR_BG);
    cleardevice();
}

// initLevel1 và runGameLevel1 đã được tách sang levels/Level1.h

void runMenu(Menu& menu) {
    while (currentState == MENU) {
        beginFrame();
        if (showInstructions) {
            // Hiển thị màn hình hướng dẫn
            menu.drawInstructions();
            
            // Chờ ESC để quay lại menu
            if (kbhit()) {
                char key = getch();
                if (key == 27) {  // ESC
                    showInstructions = false;
                }
            }
        } else {
            // Hiển thị menu chính
            menu.draw();
            
            // Kiểm tra input
            if (kbhit()) {
                char key = getch();
                
                if (key == 13 || key == '\r' || key == '\n') {  // ENTER (thử nhiều code)
                    int option = menu.getSelectedOption();
                    if (option == 0) {
                        currentState = PLAYING;  // Bắt đầu game
                        endFrame();
                        return;  // Thoát khỏi menu loop
                    } else if (option == 1) {
                        showInstructions = true;  // Xem hướng dẫn
                    } else if (option == 2) {
                        closegraph();  // Thoát
                        exit(0);
                    }
                } else if (key == 0 || key == -32) {  // Extended key
                    key = getch();
                    if (key == 72 || key == 80) {  // UP or DOWN
                        menu.setLastKey(key);
                        menu.handleInput();
                    }
                }
            }
        }
        
        endFrame();
        delay(50);  // Giảm CPU usage
    }
}

int main() {
    initGraphics();

    Menu menu;

    // Vòng đời game: Menu -> Level -> quay lại Menu (WIN/GAME OVER)
    while (true) {
        currentState = MENU;
        runMenu(menu);

        if (currentState == PLAYING) {
            runGameLevel1();
            // Sau khi chơi xong (WIN hoặc GAME OVER), lặp lại để quay lại menu
            continue;
        }

        // Nếu runMenu thoát mà không chuyển sang PLAYING (chọn Exit)
        break;
    }

    closegraph();
    return 0;
}
