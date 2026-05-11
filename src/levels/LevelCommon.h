#ifndef LEVEL_COMMON_H
#define LEVEL_COMMON_H

#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>

#include "../config.h"
#include "../core/doublebuffer.h"
#include "../core/decorations.h"
#include "../core/blocks.h"

// Lựa chọn sau khi kết thúc màn chơi (dùng chung cho nhiều level)
enum EndAction {
    END_TO_MENU = 0,
    END_RESTART = 1,
    END_NEXT    = 2
};

// Màn hình kết thúc (win/lose) dùng chung
// isLastLevel = true: Level cuối cùng, không hiện nút NEXT LEVEL kể cả khi thắng
static EndAction showEndScreen(int levelNumber, bool win, bool isLastLevel = false) {
    // Nếu level cuối và thắng: mặc định REPLAY (0); nếu thắng thường: mặc định NEXT (1); nếu thua: mặc định REPLAY (0)
    int selected = (win && !isLastLevel) ? 1 : 0;
    int frame = 0;

    // Flush bàn phím nếu còn dư phím
    while (kbhit()) getch();

    while (true) {
        frame++;
        beginFrame();
        
        // Background giống menu chính
        drawLabyrinthBackground();
        drawStars();

        // Hiệu ứng nền động
        if (win) {
            // Hạt sáng bay lên
            for (int i = 0; i < 50; i++) {
                int px = (i * 73 + frame * 2) % SCREEN_WIDTH;
                int py = SCREEN_HEIGHT - ((i * 111 + frame * 4) % SCREEN_HEIGHT);
                if (py < 0) py += SCREEN_HEIGHT;
                int c = 9 + (i % 6); // Màu sặc sỡ (9->14)
                setcolor(c);
                line(px, py - 2, px + 2, py + 2);
                line(px, py + 2, px + 2, py - 2);
            }
        } else {
            // Hiệu ứng hạt mưa buồn
            for (int i = 0; i < 50; i++) {
                int px = (i * 67 + (SCREEN_WIDTH - frame * 3) % SCREEN_WIDTH) % SCREEN_WIDTH;
                int py = (i * 103 + frame * 10) % SCREEN_HEIGHT;
                setcolor(i % 3 == 0 ? 4 : 8); // Đỏ tối hoặc xám
                line(px, py, px - 3, py + 12);
            }
        }

        // Tiêu đề với animation
        int titleY = 70;
        int titleXOffset = 0;
        int titleYOffset = 0;
        
        if (win) {
            // Nhảy múa nhẹ
            titleYOffset = (frame % 30 < 15) ? -4 : 0;
            int shadowColor = (frame % 10 < 5) ? 0x704000 : 0x502010;
            drawTextWithShadow(SCREEN_WIDTH/2 - 160, titleY + titleYOffset,
                               (char*)"YOU WIN!",
                               6, 0xFFFF80, shadowColor);
        } else {
            // Rung lắc dữ dội bối rối
            titleXOffset = (rand() % 7) - 3;
            titleYOffset = (rand() % 7) - 3;
            drawTextWithShadow(SCREEN_WIDTH/2 - 190 + titleXOffset, titleY + titleYOffset,
                               (char*)"GAME OVER",
                               6, 0xFF4444, 0x300000);
        }

        // Panel trung tâm
        int panelW = 580;
        int panelH = 360;
        int panelX = SCREEN_WIDTH/2 - panelW/2;
        int panelY = 170;
        
        int bgColor     = win ? 0x0A162A : 0x1A0808;
        int borderColor = win ? 0x3388EE : 0xAA2222;
        
        // Viền nhấp nháy cho win/lose
        if (win && (frame % 20 < 10)) borderColor = 0x66AAFF;
        if (!win && (frame % 14 < 7)) borderColor = 0xFF4444;
        
        drawPanel(panelX, panelY, panelW, panelH, bgColor, borderColor);

        // Nội dung text trong panel
        settextstyle(10, HORIZ_DIR, 2);
        const int textCenterX = SCREEN_WIDTH/2;
        
        int oldBk = getbkcolor();
        setbkcolor(HEX2COLOR(bgColor)); // Đồng bộ nền chữ với nền Panel
        
        if (win) {
            setcolor(14); // Vàng
            char line1[] = "CONGRATULATIONS!";
            outtextxy(textCenterX - textwidth(line1)/2, panelY + 30, line1);
            
            setcolor(15);
            char line2[] = "You successfully collected all keys";
            char line3[] = "and escaped the labyrinth!";
            outtextxy(textCenterX - textwidth(line2)/2, panelY + 65, line2);
            outtextxy(textCenterX - textwidth(line3)/2, panelY + 95, line3);
        } else {
            setcolor(12); // Đỏ nhạt
            char line1[] = "MISSION FAILED...";
            outtextxy(textCenterX - textwidth(line1)/2, panelY + 30, line1);
            
            setcolor(15);
            char line2[] = "You fell into hazards or enemies.";
            char line3[] = "Don't give up, try again!";
            outtextxy(textCenterX - textwidth(line2)/2, panelY + 65, line2);
            outtextxy(textCenterX - textwidth(line3)/2, panelY + 95, line3);
        }

        setcolor(7);
        char instruction[] = "[ UP / DOWN ] to move      [ ENTER ] to select";
        outtextxy(textCenterX - textwidth(instruction)/2, panelY + 135, instruction);
        
        setbkcolor(oldBk); // Phục hồi nền để không dính tới Button

        // Số nút: thắng + không phải level cuối = 3; còn lại = 2
        int numButtons = (win && !isLastLevel) ? 3 : 2;
        if (selected >= numButtons) selected = numButtons - 1;

        // Vẽ Buttons
        int cx = SCREEN_WIDTH/2;
        int btnW = 380;
        int btnH = 50;

        char replayLabel[32];
        sprintf(replayLabel, "REPLAY LEVEL %d", levelNumber);

        if (win && !isLastLevel) {
            // 3 nút: REPLAY / NEXT LEVEL / BACK TO MENU
            int btnY1 = panelY + 175;
            int btnY2 = panelY + 235;
            int btnY3 = panelY + 295;
            drawGameButton(cx, btnY1, btnW, btnH, replayLabel, selected == 0);
            drawGameButton(cx, btnY2, btnW, btnH, (char*)"NEXT LEVEL", selected == 1);
            drawGameButton(cx, btnY3, btnW, btnH, (char*)"BACK TO MENU", selected == 2);
        } else {
            // 2 nút: REPLAY / BACK TO MENU (thua hoặc level cuối thắng)
            int btnY1 = panelY + 195;
            int btnY2 = panelY + 265;
            drawGameButton(cx, btnY1, btnW, btnH, replayLabel, selected == 0);
            drawGameButton(cx, btnY2, btnW, btnH, (char*)"BACK TO MENU", selected == 1);
        }

        endFrame();
        delay(30);

        if (kbhit()) {
            char key = getch();
            if (key == 27) { // ESC -> về menu
                return END_TO_MENU;
            }

            if (key == 13 || key == '\r' || key == '\n') {
                if (win && !isLastLevel) {
                    // 3 nút
                    if (selected == 0) return END_RESTART;
                    if (selected == 1) return END_NEXT;
                    return END_TO_MENU;
                } else {
                    // 2 nút (thua hoặc level cuối)
                    if (selected == 0) return END_RESTART;
                    return END_TO_MENU;
                }
            }

            // Xử lý mũi tên
            if (key == 0 || key == -32) {
                key = getch();
                if (key == 72) { // UP
                    selected--;
                    if (selected < 0) selected = numButtons - 1;
                } else if (key == 80) { // DOWN
                    selected++;
                    if (selected >= numButtons) selected = 0;
                }
            }
        }
    }
}

// HUD cho mỗi level
static void drawLevelHUD(int levelNumber, int keysCollected, int keysRequired, bool paused) {
    // Vẽ nền HUD
    drawRect(10, 5, 200, 54, 0x111111);
    setcolor(HEX2COLOR(0x555555));
    rectangle(10, 5, 210, 59);

    int oldBk = getbkcolor();
    setbkcolor(HEX2COLOR(0x111111)); // Nền trùng với HUD panel
    
    settextstyle(10, HORIZ_DIR, 2);
    setcolor(14);

    char levelText[32];
    sprintf(levelText, "LEVEL %d", levelNumber);
    outtextxy(18, 12, levelText);

    if (keysCollected >= keysRequired) {
        setcolor(10); // Xanh lục báo hiệu đủ key
    } else {
        setcolor(15);
    }
    char keyText[64];
    sprintf(keyText, "Keys: %d / %d", keysCollected, keysRequired);
    outtextxy(18, 36, keyText);

    char hudRight[48];
    sprintf(hudRight, "P: Pause  |  ESC: Menu");
    int hudW = textwidth(hudRight);
    
    drawRect(SCREEN_WIDTH - hudW - 24, 5, hudW + 16, 32, 0x111111);
    setcolor(HEX2COLOR(0x555555));
    rectangle(SCREEN_WIDTH - hudW - 24, 5, SCREEN_WIDTH - 8, 37);
    
    setcolor(15);
    outtextxy(SCREEN_WIDTH - hudW - 16, 12, hudRight);
    
    setbkcolor(oldBk); // Khôi phục

    if (paused) {
        int pW = 340;
        int pH = 120;
        drawPanel(SCREEN_WIDTH/2 - pW/2, SCREEN_HEIGHT/2 - pH/2, pW, pH, 0x0A0A0A, 0xDDAA00);

        setbkcolor(HEX2COLOR(0x0A0A0A)); // Phải set thủ công vì không có transparent
        settextstyle(10, HORIZ_DIR, 4);
        setcolor(14);
        char pausedText[] = "PAUSED";
        int tw = textwidth(pausedText);
        outtextxy(SCREEN_WIDTH/2 - tw/2, SCREEN_HEIGHT/2 - 35, pausedText);
        
        settextstyle(10, HORIZ_DIR, 2);
        setcolor(15);
        char resumeText[] = "Press P to Resume";
        int rtw = textwidth(resumeText);
        outtextxy(SCREEN_WIDTH/2 - rtw/2, SCREEN_HEIGHT/2 + 20, resumeText);
        setbkcolor(oldBk);
    }
}

#endif // LEVEL_COMMON_H
