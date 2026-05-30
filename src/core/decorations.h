#ifndef DECORATIONS_H
#define DECORATIONS_H

#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include "fractals.h"

// vẽ mây đơn giản bằng hàm thư viện
static void drawCloud(int x, int y, int size, int color) {
    setfillstyle(SOLID_FILL, color);
    setcolor(color);
    fillellipse(x, y, size, size);
    fillellipse(x - size, y + size/2, size * 3/4, size * 3/4);
    fillellipse(x + size, y + size/2, size * 3/4, size * 3/4);
}

// background level 1
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

    // tP3
    drawKochCurve(120, 235, 310, 235, 3, COLOR(75, 65, 115));
    drawKochCurve(790, 250, 990, 250, 3, COLOR(82, 64, 125));
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

    // nen Level 3 uu tien nhe de giu FPS on dinh khi map co nhieu gai
    setcolor(COLOR(150, 115, 70));
    line(130, 615, 330, 615);
    line(700, 640, 940, 640);
}

// background level 4
static void drawLevel4Background() {
    setbkcolor(COLOR(175, 205, 230));
    cleardevice();

    // may lanh va nui bang xa xa
    drawCloud(200, 120, 22, COLOR(245, 250, 255));
    drawCloud(500, 100, 25, COLOR(240, 248, 255));
    drawCloud(850, 140, 20, COLOR(250, 252, 255));

    setfillstyle(SOLID_FILL, COLOR(210, 230, 245));
    setcolor(COLOR(210, 230, 245));
    int peak1[] = {40, 620, 190, 360, 340, 620, 40, 620};
    fillpoly(4, peak1);
    int peak2[] = {710, 630, 890, 340, 1060, 630, 710, 630};
    fillpoly(4, peak2);

    // tP3
    drawKochSnowflake(150, 210, 28, 2, COLOR(245, 250, 255));
    drawKochSnowflake(420, 165, 22, 2, COLOR(235, 248, 255));
    drawKochSnowflake(690, 230, 26, 2, COLOR(245, 250, 255));
    drawKochSnowflake(945, 185, 24, 2, COLOR(235, 248, 255));

    for (int i = 0; i < 36; i++) {
        int sx = (i * 91) % SCREEN_WIDTH;
        int sy = 70 + (i * 57) % 520;
        setcolor(COLOR(245, 250, 255));
        line(sx - 2, sy, sx + 2, sy);
        line(sx, sy - 2, sx, sy + 2);
    }
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

    // tP3
    drawDragonCurve(465, 120, 635, 120, 5, 1, COLOR(0, 140, 125));
    drawKochCurve(390, 705, 710, 705, 2, COLOR(90, 105, 150));
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
