#ifndef DECORATIONS_H
#define DECORATIONS_H

#include <graphics.h>
#include <stdlib.h>
#include <time.h>

// vẽ mây đơn giản bằng hàm thư viện (nhanh)
static void drawCloud(int x, int y, int size, int color) {
    setfillstyle(SOLID_FILL, color);
    setcolor(color);
    fillellipse(x, y, size, size);
    fillellipse(x - size, y + size/2, size * 3/4, size * 3/4);
    fillellipse(x + size, y + size/2, size * 3/4, size * 3/4);
}

// background level 1: đơn giản nhất
static void drawLevel1Background() {
    setbkcolor(COLOR(100, 150, 200));
    cleardevice();
    
    // mặt trời
    setfillstyle(SOLID_FILL, COLOR(255, 220, 100));
    setcolor(COLOR(255, 220, 100));
    fillellipse(150, 120, 40, 40);
    
    // mây
    drawCloud(300, 150, 25, COLOR(240, 240, 250));
    drawCloud(600, 100, 30, COLOR(235, 235, 245));
    drawCloud(900, 180, 28, COLOR(245, 245, 255));
}

// background level 2
static void drawLevel2Background() {
    setbkcolor(COLOR(15, 10, 25));
    cleardevice();
    
    // vòng tròn đồng tâm
    int centerX = SCREEN_WIDTH / 2, centerY = SCREEN_HEIGHT / 2;
    for (int i = 10; i > 0; i--) {
        setcolor(COLOR(15 + i * 3, 10 + i * 3, 25 + i * 5));
        circle(centerX, centerY, i * 70);
    }
}

// background level 3
static void drawLevel3Background() {
    setbkcolor(COLOR(194, 178, 128));
    cleardevice();
    
    // mặt trời
    setfillstyle(SOLID_FILL, COLOR(255, 200, 80));
    setcolor(COLOR(255, 200, 80));
    fillellipse(900, 150, 50, 50);
    
    // mây
    drawCloud(250, 180, 20, COLOR(220, 220, 230));
    drawCloud(700, 150, 18, COLOR(215, 215, 225));
}

// background level 4
static void drawLevel4Background() {
    setbkcolor(COLOR(100, 150, 100));
    cleardevice();
    
    // mây
    drawCloud(200, 120, 22, COLOR(240, 245, 250));
    drawCloud(500, 100, 25, COLOR(235, 240, 245));
    drawCloud(850, 140, 20, COLOR(245, 250, 255));
}

// background level 5
static void drawLevel5Background() {
    setbkcolor(COLOR(5, 5, 20));
    cleardevice();
    
    // vẽ sao nhỏ
    for (int i = 0; i < 50; i++) {
        int x = (i * 137) % SCREEN_WIDTH;
        int y = (i * 211) % SCREEN_HEIGHT;
        putpixel(x, y, COLOR(255, 255, 255));
    }
    
    // hành tinh
    setfillstyle(SOLID_FILL, COLOR(120, 60, 180));
    setcolor(COLOR(120, 60, 180));
    fillellipse(200, 250, 60, 60);
    
    setfillstyle(SOLID_FILL, COLOR(220, 120, 70));
    setcolor(COLOR(220, 120, 70));
    fillellipse(900, 500, 45, 45);
}

// vẽ sao lấp lánh
static void drawStars() {
    static int frame = 0;
    frame++;
    int stars[][2] = {{850,200},{950,150},{1050,250},{150,300},{100,450},{1100,500},{50,630},{1000,650}};
    for (int i = 0; i < 8; i++) {
        int sx = stars[i][0], sy = stars[i][1];
        int phase = (frame + i * 7) % 60;
        bool bright = (phase < 25);
        int mainLen = bright ? 6 : 3;
        int color = bright ? 15 : 8;
        setcolor(color);
        line(sx - mainLen, sy, sx + mainLen, sy);
        line(sx, sy - mainLen, sx, sy + mainLen);
    }
}

// vẽ title
static void drawGameTitle(int x, int y) {
    settextstyle(10, HORIZ_DIR, 7);
    char title[] = "PARKOUR 2D";
    setcolor(0);
    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
            if (dx != 0 || dy != 0) {
                outtextxy(x + dx, y + dy, title);
            }
        }
    }
    setcolor(14);
    outtextxy(x, y, title);
    settextstyle(10, HORIZ_DIR, 2);
    setcolor(15);
    char subtitle[] = "ESCAPE THE LABYRINTH";
    outtextxy(x + 60, y + 70, subtitle);
}

// background menu
static void drawLabyrinthBackground() {
    drawLevel1Background();
}

#endif
