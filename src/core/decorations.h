#ifndef DECORATIONS_H
#define DECORATIONS_H

#include <graphics.h>
#include <stdlib.h>
#include <time.h>

// ============================================================
//  Vẽ background đơn giản
// ============================================================
static void drawLabyrinthBackground() {
    setbkcolor(1);  // Xanh đậm
    cleardevice();
    
    // Vẽ các đường mê cung mờ ở background (không có chữ)
    setcolor(9);  // Xanh nhạt
    setlinestyle(SOLID_LINE, 0, 1);
    
    // Vertical lines
    for (int i = 0; i < 20; i++) {
        int x = 50 + i * 60;
        line(x, 0, x, SCREEN_HEIGHT);
    }
    
    // Horizontal lines
    for (int i = 0; i < 15; i++) {
        int y = 50 + i * 60;
        line(0, y, SCREEN_WIDTH, y);
    }
}

// ============================================================
//  Vẽ các ngôi sao trang trí
// ============================================================
static void drawStars() {
    // Biến frame tĩnh để tạo hiệu ứng lấp lánh theo thời gian
    static int frame = 0;
    frame++;

    // Vị trí các ngôi sao cố định
    int stars[][2] = {
        {850, 200}, {950, 150}, {1050, 250},
        {150, 300}, {100, 450}, {1100, 500},
        {50, 630}, {1000, 650}
    };

    for (int i = 0; i < 8; i++) {
        int sx = stars[i][0];
        int sy = stars[i][1];

        // Mỗi ngôi sao lệch pha một chút
        int phase = (frame + i * 7) % 60; // chu kỳ ~60 frame

        // Xác định độ sáng & kích thước theo phase
        bool bright = (phase < 25);           // sáng hơn nửa chu kỳ
        int mainLen = bright ? 6 : 3;         // độ dài cánh dọc/ngang
        int diagLen = bright ? 4 : 2;         // độ dài cánh chéo

        int color = bright ? 15 : 8;          // trắng sáng hoặc xám nhạt
        setcolor(color);

        // Vẽ ngôi sao 4 cánh
        line(sx - mainLen, sy, sx + mainLen, sy);
        line(sx, sy - mainLen, sx, sy + mainLen);
        line(sx - diagLen, sy - diagLen, sx + diagLen, sy + diagLen);
        line(sx - diagLen, sy + diagLen, sx + diagLen, sy - diagLen);
    }
}

// ============================================================
//  Vẽ title với hiệu ứng outline
// ============================================================
static void drawGameTitle(int x, int y) {
    settextstyle(10, HORIZ_DIR, 7);
    char title[] = "PARKOUR 2D";
    
    // Outline đen dày
    setcolor(0);
    for (int dx = -3; dx <= 3; dx++) {
        for (int dy = -3; dy <= 3; dy++) {
            if (dx != 0 || dy != 0) {
                outtextxy(x + dx, y + dy, title);
            }
        }
    }
    
    // Outline nâu
    setcolor(6);
    outtextxy(x - 2, y - 2, title);
    outtextxy(x + 2, y - 2, title);
    outtextxy(x - 2, y + 2, title);
    outtextxy(x + 2, y + 2, title);
    
    // Text vàng chính
    setcolor(14);
    outtextxy(x, y, title);
    
    // Subtitle
    settextstyle(10, HORIZ_DIR, 2);
    setcolor(15);
    char subtitle[] = "ESCAPE THE LABYRINTH";
    outtextxy(x + 60, y + 70, subtitle);
}

#endif
