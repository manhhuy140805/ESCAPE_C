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

// Hàm vẽ mạng nhện ở góc
static void drawSpiderWeb(int x0, int y0, int dirX, int dirY, int size) {
    setcolor(COLOR(90, 90, 100)); // Màu tơ nhện
    int spokesX[] = {0, 33, 70, 95, 100};
    int spokesY[] = {100, 95, 70, 33, 0};
    for (int i = 0; i < 5; i++) {
        line(x0, y0, x0 + dirX * spokesX[i] * size / 100, y0 + dirY * spokesY[i] * size / 100);
    }
    for (int r = 1; r <= 5; r++) {
        float scale = r / 5.0f;
        for (int i = 0; i < 4; i++) {
            int px1 = x0 + dirX * spokesX[i] * size / 100 * scale;
            int py1 = y0 + dirY * spokesY[i] * size / 100 * scale;
            int px2 = x0 + dirX * spokesX[i+1] * size / 100 * scale;
            int py2 = y0 + dirY * spokesY[i+1] * size / 100 * scale;
            line(px1, py1, px2, py2);
        }
    }
}

// background level 2
static void drawLevel2Background() {
    // Màu nền hang nhện (xanh rêu đen)
    setbkcolor(COLOR(10, 15, 10));
    cleardevice();
    
    // Vách đá trên trần
    setfillstyle(SOLID_FILL, COLOR(25, 30, 25));
    setcolor(COLOR(25, 30, 25));
    int ceiling[] = {
        0, 0,
        150, 180,
        300, 50,
        450, 220,
        600, 80,
        750, 250,
        950, 90,
        1100, 160,
        SCREEN_WIDTH, 50,
        SCREEN_WIDTH, 0,
        0, 0
    };
    fillpoly(11, ceiling);

    // Đá ngầm dưới đáy hang
    setfillstyle(SOLID_FILL, COLOR(20, 25, 20));
    setcolor(COLOR(20, 25, 20));
    int floor[] = {
        0, SCREEN_HEIGHT,
        150, SCREEN_HEIGHT - 120,
        350, SCREEN_HEIGHT - 180,
        550, SCREEN_HEIGHT - 100,
        750, SCREEN_HEIGHT - 200,
        950, SCREEN_HEIGHT - 90,
        SCREEN_WIDTH, SCREEN_HEIGHT - 150,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        0, SCREEN_HEIGHT
    };
    fillpoly(9, floor);

    // Hoa văn nứt nẻ trên vách đá (tP3 Fractal - cần thiết cho chấm điểm)
    drawKochCurve(150, SCREEN_HEIGHT - 120, 350, SCREEN_HEIGHT - 180, 3, COLOR(40, 45, 40));
    drawKochCurve(550, SCREEN_HEIGHT - 100, 750, SCREEN_HEIGHT - 200, 3, COLOR(35, 40, 35));
    drawKochCurve(950, SCREEN_HEIGHT - 90, SCREEN_WIDTH, SCREEN_HEIGHT - 150, 3, COLOR(30, 35, 30));

    // Rễ cây mọc rủ xuống (tP3 Fractal Rồng - cần thiết cho chấm điểm)
    drawDragonCurve(450, 220, 450, 450, 5, 1, COLOR(45, 55, 45));
    drawDragonCurve(750, 250, 750, 500, 6, 1, COLOR(35, 45, 35));

    // Vẽ mạng nhện ở các góc và giữa trần
    drawSpiderWeb(0, 0, 1, 1, 350); // Góc trên trái
    drawSpiderWeb(SCREEN_WIDTH, 0, -1, 1, 400); // Góc trên phải
    drawSpiderWeb(0, SCREEN_HEIGHT, 1, -1, 250); // Góc dưới trái
    drawSpiderWeb(SCREEN_WIDTH, SCREEN_HEIGHT, -1, -1, 300); // Góc dưới phải
    
    // Mạng nhện rủ từ trần
    drawSpiderWeb(600, 0, 1, 1, 200);
    drawSpiderWeb(600, 0, -1, 1, 200);
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
