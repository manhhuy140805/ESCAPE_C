#ifndef CUSTOM_DRAWING_H
#define CUSTOM_DRAWING_H

#include "../core/algorithms.h"
#include "../config.h"

// áP DỤNG THUẬT TOÁN VẼ VÀO GAME

/**
 * Vẽ nhân vật đơn giản sử dụng các thuật toán tự cài đặt
 * Sử dụng: Bresenham Line, Midpoint Circle
 */
static void drawCustomPlayer(int x, int y, bool facingRight, int color) {
    // đầu
    midpointCircle(x, y - 24, 8, COLOR(255, 220, 180));
    filledMidpointCircle(x, y - 24, 7, COLOR(255, 220, 180));
    
    // thân
    bresenhamLine(x, y - 16, x, y - 8, COLOR(40, 150, 60)); // thân dọc
    
    // tay trái
    if (facingRight) {
        bresenhamLine(x, y - 14, x - 6, y - 10, COLOR(255, 220, 180));
    } else {
        bresenhamLine(x, y - 14, x + 6, y - 10, COLOR(255, 220, 180));
    }
    
    // tay phải
    if (facingRight) {
        bresenhamLine(x, y - 14, x + 6, y - 10, COLOR(255, 220, 180));
    } else {
        bresenhamLine(x, y - 14, x - 6, y - 10, COLOR(255, 220, 180));
    }
    
    // chân trái
    bresenhamLine(x, y - 8, x - 4, y, COLOR(30, 40, 80));
    
    // chân phải
    bresenhamLine(x, y - 8, x + 4, y, COLOR(30, 40, 80));
    
    // mắt
    if (facingRight) {
        filledMidpointCircle(x + 3, y - 24, 1, COLOR(0, 0, 0));
    } else {
        filledMidpointCircle(x - 3, y - 24, 1, COLOR(0, 0, 0));
    }
}

/**
 * Vẽ enemy đơn giản sử dụng các thuật toán tự cài đặt
 */
static void drawCustomEnemy(int x, int y, bool facingRight) {
    // đầu
    midpointCircle(x, y - 24, 8, COLOR(180, 30, 30));
    filledMidpointCircle(x, y - 24, 7, COLOR(180, 30, 30));
    
    // thân
    bresenhamLine(x, y - 16, x, y - 8, COLOR(80, 80, 90));
    
    // tay với vũ khí
    if (facingRight) {
        bresenhamLine(x, y - 14, x + 8, y - 12, COLOR(180, 30, 30));
        bresenhamLine(x + 8, y - 12, x + 12, y - 10, COLOR(180, 180, 200)); // vũ khí
    } else {
        bresenhamLine(x, y - 14, x - 8, y - 12, COLOR(180, 30, 30));
        bresenhamLine(x - 8, y - 12, x - 12, y - 10, COLOR(180, 180, 200)); // vũ khí
    }
    
    // chân
    bresenhamLine(x, y - 8, x - 4, y, COLOR(50, 50, 60));
    bresenhamLine(x, y - 8, x + 4, y, COLOR(50, 50, 60));
    
    // mắt phát sáng
    if (facingRight) {
        filledMidpointCircle(x + 3, y - 24, 2, COLOR(255, 220, 0));
    } else {
        filledMidpointCircle(x - 3, y - 24, 2, COLOR(255, 220, 0));
    }
}

/**
 * Vẽ đạn sử dụng Midpoint Circle
 */
static void drawCustomBullet(int x, int y, bool isPlayerBullet) {
    if (isPlayerBullet) {
        // đạn player
        midpointCircle(x, y, 5, COLOR(0, 150, 255));
        filledMidpointCircle(x, y, 4, COLOR(200, 240, 255));
    } else {
        // đạn enemy
        midpointCircle(x, y, 5, COLOR(255, 80, 0));
        filledMidpointCircle(x, y, 4, COLOR(255, 220, 100));
    }
}

/**
 * Vẽ chìa khóa sử dụng các thuật toán tự cài đặt
 */
static void drawCustomKey(int x, int y) {
    // đầu chìa khóa
    midpointCircle(x, y - 8, 4, COLOR(255, 215, 0));
    filledMidpointCircle(x, y - 8, 3, COLOR(255, 215, 0));
    
    // lỗ khóa nhỏ
    filledMidpointCircle(x, y - 8, 1, COLOR(100, 100, 0));
    
    // thân chìa khóa
    bresenhamLine(x, y - 4, x, y + 4, COLOR(255, 215, 0));
    
    // răng chìa khóa
    bresenhamLine(x, y, x + 2, y, COLOR(255, 215, 0));
    bresenhamLine(x, y + 3, x + 2, y + 3, COLOR(255, 215, 0));
}

/**
 * Vẽ cửa sử dụng Bresenham Rectangle và Line
 */
static void drawCustomDoor(int x, int y, bool isOpen) {
    int doorColor = isOpen ? COLOR(100, 255, 100) : COLOR(139, 69, 19);
    
    // khung cửa
    bresenhamRectangle(x - 12, y - 40, x + 12, y, doorColor);
    
    if (!isOpen) {
        // tay nắm
        filledMidpointCircle(x + 6, y - 20, 2, COLOR(255, 215, 0));
        
        // các đường trang trí
        bresenhamLine(x - 8, y - 35, x - 8, y - 5, COLOR(100, 50, 10));
        bresenhamLine(x + 8, y - 35, x + 8, y - 5, COLOR(100, 50, 10));
        bresenhamLine(x - 8, y - 20, x + 8, y - 20, COLOR(100, 50, 10));
    }
}

/**
 * Vẽ trái tim (HP) sử dụng Midpoint Circle và Bresenham Triangle
 */
static void drawCustomHeart(int x, int y, bool isFilled) {
    int heartColor = isFilled ? COLOR(255, 50, 50) : COLOR(80, 80, 80);
    
    // 2 nửa tròn trên
    filledMidpointCircle(x - 4, y, 4, heartColor);
    filledMidpointCircle(x + 4, y, 4, heartColor);
    
    // tam giác dưới
    bresenhamTriangle(x - 8, y, x + 8, y, x, y + 10, heartColor);
    
    // tô màu tam giác
    for (int dy = 0; dy <= 10; dy++) {
        int width = 8 - (dy * 8 / 10);
        bresenhamLine(x - width, y + dy, x + width, y + dy, heartColor);
    }
}

/**
 * Vẽ hiệu ứng nổ (explosion) sử dụng Bresenham Line
 */
static void drawCustomExplosion(int x, int y, int frame) {
    int radius = 5 + frame * 2;
    int color = COLOR(255, 200 - frame * 20, 0);
    
    // vẽ các tia nổ theo 8 hướng
    for (int angle = 0; angle < 360; angle += 45) {
        float rad = angle * 3.14159 / 180.0;
        int x2 = x + radius * cos(rad);
        int y2 = y + radius * sin(rad);
        bresenhamLine(x, y, x2, y2, color);
    }
    
    // vòng tròn bên ngoài
    midpointCircle(x, y, radius, color);
}

/**
 * Vẽ nền sao lấp lánh sử dụng Midpoint Circle
 */
static void drawCustomStar(int x, int y, int size, int brightness) {
    int color = COLOR(brightness, brightness, brightness);
    
    // tâm sao
    filledMidpointCircle(x, y, size, color);
    
    // các tia sáng
    bresenhamLine(x - size * 2, y, x + size * 2, y, color);
    bresenhamLine(x, y - size * 2, x, y + size * 2, color);
    bresenhamLine(x - size, y - size, x + size, y + size, color);
    bresenhamLine(x - size, y + size, x + size, y - size, color);
}

/**
 * Vẽ nền mê cung sử dụng Bresenham Line
 */
static void drawCustomMazeBackground() {
    // vẽ lưới mê cung
    for (int i = 0; i < SCREEN_WIDTH; i += 40) {
        bresenhamLine(i, 0, i + 20, SCREEN_HEIGHT, COLOR(20, 30, 50));
    }
    
    for (int j = 0; j < SCREEN_HEIGHT; j += 40) {
        bresenhamLine(0, j, SCREEN_WIDTH, j + 20, COLOR(20, 30, 50));
    }
}

// áP DỤNG THUẬT TOÁN FLOOD FILL VÀO GAME

/**
 * Vẽ nhân vật với tô màu Flood Fill
 * Tô màu đầy đủ các phần của nhân vật
 */
static void drawFilledPlayer(int x, int y, bool facingRight) {
    // đầu
    midpointCircle(x, y - 24, 8, COLOR(100, 50, 0));
    floodFill(x, y - 24, COLOR(255, 220, 180));
    
    // thân
    bresenhamRectangle(x - 6, y - 16, x + 6, y - 8, COLOR(0, 100, 0));
    floodFill(x, y - 12, COLOR(40, 150, 60));
    
    // tay trái
    int armPoints1[] = {
        x - 6, y - 14,
        x - 10, y - 10,
        x - 8, y - 8,
        x - 4, y - 12
    };
    filledPolygon(armPoints1, 4, COLOR(100, 50, 0), COLOR(255, 220, 180), x - 7, y - 11);
    
    // tay phải
    int armPoints2[] = {
        x + 6, y - 14,
        x + 10, y - 10,
        x + 8, y - 8,
        x + 4, y - 12
    };
    filledPolygon(armPoints2, 4, COLOR(100, 50, 0), COLOR(255, 220, 180), x + 7, y - 11);
    
    // chân trái
    int legPoints1[] = {
        x - 2, y - 8,
        x - 6, y,
        x - 4, y,
        x, y - 8
    };
    filledPolygon(legPoints1, 4, COLOR(0, 0, 100), COLOR(30, 40, 80), x - 3, y - 4);
    
    // chân phải
    int legPoints2[] = {
        x + 2, y - 8,
        x + 6, y,
        x + 4, y,
        x, y - 8
    };
    filledPolygon(legPoints2, 4, COLOR(0, 0, 100), COLOR(30, 40, 80), x + 3, y - 4);
    
    // mắt
    if (facingRight) {
        filledMidpointCircle(x + 3, y - 24, 2, COLOR(0, 0, 0));
    } else {
        filledMidpointCircle(x - 3, y - 24, 2, COLOR(0, 0, 0));
    }
}

/**
 * Vẽ enemy với tô màu Flood Fill
 */
static void drawFilledEnemy(int x, int y, bool facingRight) {
    // đầu
    midpointCircle(x, y - 24, 8, COLOR(100, 0, 0));
    floodFill(x, y - 24, COLOR(180, 30, 30));
    
    // thân
    bresenhamRectangle(x - 6, y - 16, x + 6, y - 8, COLOR(50, 50, 50));
    floodFill(x, y - 12, COLOR(80, 80, 90));
    
    // tay với vũ khí
    if (facingRight) {
        int armPoints[] = {
            x, y - 14,
            x + 8, y - 12,
            x + 8, y - 10,
            x, y - 12
        };
        filledPolygon(armPoints, 4, COLOR(100, 0, 0), COLOR(180, 30, 30), x + 4, y - 12);
        
        // vũ khí
        filledRectangle(x + 8, y - 13, x + 14, y - 9, COLOR(100, 100, 100), COLOR(180, 180, 200));
    } else {
        int armPoints[] = {
            x, y - 14,
            x - 8, y - 12,
            x - 8, y - 10,
            x, y - 12
        };
        filledPolygon(armPoints, 4, COLOR(100, 0, 0), COLOR(180, 30, 30), x - 4, y - 12);
        
        // vũ khí
        filledRectangle(x - 14, y - 13, x - 8, y - 9, COLOR(100, 100, 100), COLOR(180, 180, 200));
    }
    
    // chân
    int legPoints1[] = {x - 2, y - 8, x - 6, y, x - 4, y, x, y - 8};
    filledPolygon(legPoints1, 4, COLOR(30, 30, 30), COLOR(50, 50, 60), x - 3, y - 4);
    
    int legPoints2[] = {x + 2, y - 8, x + 6, y, x + 4, y, x, y - 8};
    filledPolygon(legPoints2, 4, COLOR(30, 30, 30), COLOR(50, 50, 60), x + 3, y - 4);
    
    // mắt phát sáng
    if (facingRight) {
        filledMidpointCircle(x + 3, y - 24, 2, COLOR(255, 220, 0));
    } else {
        filledMidpointCircle(x - 3, y - 24, 2, COLOR(255, 220, 0));
    }
}

/**
 * Vẽ chìa khóa với tô màu Flood Fill
 */
static void drawFilledKey(int x, int y) {
    // đầu chìa khóa
    midpointCircle(x, y - 8, 5, COLOR(150, 120, 0));
    floodFill(x, y - 8, COLOR(255, 215, 0));
    
    // lỗ khóa nhỏ
    midpointCircle(x, y - 8, 2, COLOR(150, 120, 0));
    floodFill(x, y - 8, COLOR(100, 100, 0));
    
    // thân chìa khóa
    filledRectangle(x - 1, y - 3, x + 1, y + 5, COLOR(150, 120, 0), COLOR(255, 215, 0));
    
    // răng chìa khóa
    filledRectangle(x + 1, y - 1, x + 3, y + 1, COLOR(150, 120, 0), COLOR(255, 215, 0));
    filledRectangle(x + 1, y + 2, x + 3, y + 4, COLOR(150, 120, 0), COLOR(255, 215, 0));
}

/**
 * Vẽ cửa với tô màu Flood Fill
 */
static void drawFilledDoor(int x, int y, bool isOpen) {
    int doorColor = isOpen ? COLOR(100, 255, 100) : COLOR(139, 69, 19);
    int borderColor = isOpen ? COLOR(50, 150, 50) : COLOR(80, 40, 10);
    
    // khung cửa
    filledRectangle(x - 12, y - 40, x + 12, y, borderColor, doorColor);
    
    if (!isOpen) {
        // tay nắm
        midpointCircle(x + 6, y - 20, 3, COLOR(150, 120, 0));
        floodFill(x + 6, y - 20, COLOR(255, 215, 0));
        
        // các ô trang trí
        filledRectangle(x - 9, y - 35, x - 3, y - 25, COLOR(80, 40, 10), COLOR(100, 50, 10));
        filledRectangle(x + 3, y - 35, x + 9, y - 25, COLOR(80, 40, 10), COLOR(100, 50, 10));
        filledRectangle(x - 9, y - 15, x - 3, y - 5, COLOR(80, 40, 10), COLOR(100, 50, 10));
        filledRectangle(x + 3, y - 15, x + 9, y - 5, COLOR(80, 40, 10), COLOR(100, 50, 10));
    }
}

/**
 * Vẽ rương kho báu với tô màu Flood Fill
 */
static void drawFilledTreasureChest(int x, int y, bool isOpen) {
    if (isOpen) {
        // nắp rương mở
        filledRectangle(x - 15, y - 25, x + 15, y - 20, COLOR(100, 50, 0), COLOR(139, 69, 19));
        
        // thân rương
        filledRectangle(x - 15, y - 20, x + 15, y, COLOR(100, 50, 0), COLOR(160, 82, 45));
        
        // vàng bên trong
        for (int i = 0; i < 5; i++) {
            int cx = x - 10 + i * 5;
            int cy = y - 15 + (i % 2) * 3;
            midpointCircle(cx, cy, 2, COLOR(150, 120, 0));
            floodFill(cx, cy, COLOR(255, 215, 0));
        }
    } else {
        // rương đóng
        filledRectangle(x - 15, y - 20, x + 15, y, COLOR(100, 50, 0), COLOR(139, 69, 19));
        
        // khóa
        filledRectangle(x - 3, y - 12, x + 3, y - 8, COLOR(150, 120, 0), COLOR(255, 215, 0));
    }
    
    // viền kim loại
    bresenhamLine(x - 15, y - 10, x + 15, y - 10, COLOR(180, 180, 200));
    bresenhamLine(x, y - 20, x, y, COLOR(180, 180, 200));
}

/**
 * Vẽ cây với tô màu Flood Fill
 */
static void drawFilledTree(int x, int y) {
    // thân cây
    filledRectangle(x - 5, y - 30, x + 5, y, COLOR(80, 40, 10), COLOR(139, 69, 19));
    
    // tán lá
    midpointCircle(x - 8, y - 35, 10, COLOR(0, 80, 0));
    floodFill(x - 8, y - 35, COLOR(34, 139, 34));
    
    midpointCircle(x + 8, y - 35, 10, COLOR(0, 80, 0));
    floodFill(x + 8, y - 35, COLOR(34, 139, 34));
    
    midpointCircle(x, y - 45, 12, COLOR(0, 80, 0));
    floodFill(x, y - 45, COLOR(50, 205, 50));
}

/**
 * Vẽ đám mây với tô màu Flood Fill
 */
static void drawFilledCloud(int x, int y) {
    // 3 vòng tròn tạo thành đám mây
    midpointCircle(x - 10, y, 8, COLOR(200, 200, 200));
    floodFill(x - 10, y, COLOR(240, 240, 240));
    
    midpointCircle(x, y - 5, 10, COLOR(200, 200, 200));
    floodFill(x, y - 5, COLOR(240, 240, 240));
    
    midpointCircle(x + 10, y, 8, COLOR(200, 200, 200));
    floodFill(x + 10, y, COLOR(240, 240, 240));
}

/**
 * Vẽ ngôi sao 5 cánh với tô màu Flood Fill
 */
static void drawFilledStar5(int x, int y, int size) {
    // tính toán 5 đỉnh ngôi sao
    int points[10];
    for (int i = 0; i < 5; i++) {
        float angle = -90 + i * 72; // 72 độ giữa các đỉnh
        float rad = angle * M_PI / 180.0;
        points[i * 2] = x + size * cos(rad);
        points[i * 2 + 1] = y + size * sin(rad);
    }
    
    // vẽ ngôi sao bằng cách nối các đỉnh
    bresenhamLine(points[0], points[1], points[6], points[7], COLOR(200, 150, 0));
    bresenhamLine(points[6], points[7], points[4], points[5], COLOR(200, 150, 0));
    bresenhamLine(points[4], points[5], points[2], points[3], COLOR(200, 150, 0));
    bresenhamLine(points[2], points[3], points[8], points[9], COLOR(200, 150, 0));
    bresenhamLine(points[8], points[9], points[0], points[1], COLOR(200, 150, 0));
    
    // tô màu
    floodFill(x, y, COLOR(255, 215, 0));
}

// tP4

static void transformPoint2D(int cx, int cy, float localX, float localY,
                             float angleDeg, float scale, int &outX, int &outY) {
    float rad = angleDeg * (float)M_PI / 180.0f;
    float sx = localX * scale;
    float sy = localY * scale;
    outX = cx + (int)(sx * cos(rad) - sy * sin(rad));
    outY = cy + (int)(sx * sin(rad) + sy * cos(rad));
}

static void drawAffineKey(int x, int y, int frame) {
    float spin = frame * 0.12f;
    float scaleX = 0.25f + 0.75f * fabs(cos(spin));
    float scaleY = 1.0f + 0.08f * sin(frame * 0.10f);

    int cx = x;
    int cy = y - TILE_SIZE + 3 + (int)(2.0f * sin(frame * 0.08f));
    int headColor = COLOR(255, 220, 40);
    int edgeColor = COLOR(155, 115, 0);

    int headRx = (int)(5 * scaleX);
    if (headRx < 2) headRx = 2;
    midpointEllipse(cx, cy, headRx, (int)(5 * scaleY), edgeColor);
    filledMidpointCircle(cx, cy, (int)(3 * scaleY), headColor);

    int x1 = cx;
    int y1 = cy + (int)(4 * scaleY);
    int x2 = cx;
    int y2 = cy + (int)(18 * scaleY);
    bresenhamLine(x1, y1, x2, y2, headColor);
    bresenhamLine(x1 + 1, y1, x2 + 1, y2, headColor);

    int tooth1 = (int)(8 * scaleX);
    int tooth2 = (int)(6 * scaleX);
    if (tooth1 < 2) tooth1 = 2;
    if (tooth2 < 2) tooth2 = 2;
    bresenhamLine(cx, cy + (int)(14 * scaleY), cx + tooth1, cy + (int)(14 * scaleY), headColor);
    bresenhamLine(cx, cy + (int)(18 * scaleY), cx + tooth2, cy + (int)(18 * scaleY), headColor);
}

#endif // cUSTOM_DRAWING_H
