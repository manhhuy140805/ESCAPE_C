#ifndef CUSTOM_DRAWING_H
#define CUSTOM_DRAWING_H

#include "../core/algorithms.h"
#include "../config.h"

// ============================================================
//  ÁP DỤNG THUẬT TOÁN VẼ VÀO GAME
//  Sử dụng các thuật toán Bresenham và Midpoint đã tự cài đặt
// ============================================================

/**
 * Vẽ nhân vật đơn giản sử dụng các thuật toán tự cài đặt
 * Sử dụng: Bresenham Line, Midpoint Circle
 */
static void drawCustomPlayer(int x, int y, bool facingRight, int color) {
    // Đầu - sử dụng Midpoint Circle
    midpointCircle(x, y - 24, 8, COLOR(255, 220, 180));
    filledMidpointCircle(x, y - 24, 7, COLOR(255, 220, 180));
    
    // Thân - sử dụng Bresenham Line
    bresenhamLine(x, y - 16, x, y - 8, COLOR(40, 150, 60));  // Thân dọc
    
    // Tay trái
    if (facingRight) {
        bresenhamLine(x, y - 14, x - 6, y - 10, COLOR(255, 220, 180));
    } else {
        bresenhamLine(x, y - 14, x + 6, y - 10, COLOR(255, 220, 180));
    }
    
    // Tay phải
    if (facingRight) {
        bresenhamLine(x, y - 14, x + 6, y - 10, COLOR(255, 220, 180));
    } else {
        bresenhamLine(x, y - 14, x - 6, y - 10, COLOR(255, 220, 180));
    }
    
    // Chân trái
    bresenhamLine(x, y - 8, x - 4, y, COLOR(30, 40, 80));
    
    // Chân phải
    bresenhamLine(x, y - 8, x + 4, y, COLOR(30, 40, 80));
    
    // Mắt - sử dụng Midpoint Circle nhỏ
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
    // Đầu - Midpoint Circle màu đỏ
    midpointCircle(x, y - 24, 8, COLOR(180, 30, 30));
    filledMidpointCircle(x, y - 24, 7, COLOR(180, 30, 30));
    
    // Thân
    bresenhamLine(x, y - 16, x, y - 8, COLOR(80, 80, 90));
    
    // Tay với vũ khí
    if (facingRight) {
        bresenhamLine(x, y - 14, x + 8, y - 12, COLOR(180, 30, 30));
        bresenhamLine(x + 8, y - 12, x + 12, y - 10, COLOR(180, 180, 200));  // Vũ khí
    } else {
        bresenhamLine(x, y - 14, x - 8, y - 12, COLOR(180, 30, 30));
        bresenhamLine(x - 8, y - 12, x - 12, y - 10, COLOR(180, 180, 200));  // Vũ khí
    }
    
    // Chân
    bresenhamLine(x, y - 8, x - 4, y, COLOR(50, 50, 60));
    bresenhamLine(x, y - 8, x + 4, y, COLOR(50, 50, 60));
    
    // Mắt phát sáng - Midpoint Circle màu vàng
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
        // Đạn player - xanh cyan
        midpointCircle(x, y, 5, COLOR(0, 150, 255));
        filledMidpointCircle(x, y, 4, COLOR(200, 240, 255));
    } else {
        // Đạn enemy - đỏ cam
        midpointCircle(x, y, 5, COLOR(255, 80, 0));
        filledMidpointCircle(x, y, 4, COLOR(255, 220, 100));
    }
}

/**
 * Vẽ chìa khóa sử dụng các thuật toán tự cài đặt
 */
static void drawCustomKey(int x, int y) {
    // Đầu chìa khóa - Midpoint Circle
    midpointCircle(x, y - 8, 4, COLOR(255, 215, 0));
    filledMidpointCircle(x, y - 8, 3, COLOR(255, 215, 0));
    
    // Lỗ khóa nhỏ
    filledMidpointCircle(x, y - 8, 1, COLOR(100, 100, 0));
    
    // Thân chìa khóa - Bresenham Line
    bresenhamLine(x, y - 4, x, y + 4, COLOR(255, 215, 0));
    
    // Răng chìa khóa
    bresenhamLine(x, y, x + 2, y, COLOR(255, 215, 0));
    bresenhamLine(x, y + 3, x + 2, y + 3, COLOR(255, 215, 0));
}

/**
 * Vẽ cửa sử dụng Bresenham Rectangle và Line
 */
static void drawCustomDoor(int x, int y, bool isOpen) {
    int doorColor = isOpen ? COLOR(100, 255, 100) : COLOR(139, 69, 19);
    
    // Khung cửa
    bresenhamRectangle(x - 12, y - 40, x + 12, y, doorColor);
    
    if (!isOpen) {
        // Tay nắm - Midpoint Circle
        filledMidpointCircle(x + 6, y - 20, 2, COLOR(255, 215, 0));
        
        // Các đường trang trí
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
    
    // Tam giác dưới
    bresenhamTriangle(x - 8, y, x + 8, y, x, y + 10, heartColor);
    
    // Tô màu tam giác
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
    
    // Vẽ các tia nổ theo 8 hướng
    for (int angle = 0; angle < 360; angle += 45) {
        float rad = angle * 3.14159 / 180.0;
        int x2 = x + radius * cos(rad);
        int y2 = y + radius * sin(rad);
        bresenhamLine(x, y, x2, y2, color);
    }
    
    // Vòng tròn bên ngoài
    midpointCircle(x, y, radius, color);
}

/**
 * Vẽ nền sao lấp lánh sử dụng Midpoint Circle
 */
static void drawCustomStar(int x, int y, int size, int brightness) {
    int color = COLOR(brightness, brightness, brightness);
    
    // Tâm sao
    filledMidpointCircle(x, y, size, color);
    
    // Các tia sáng
    bresenhamLine(x - size * 2, y, x + size * 2, y, color);
    bresenhamLine(x, y - size * 2, x, y + size * 2, color);
    bresenhamLine(x - size, y - size, x + size, y + size, color);
    bresenhamLine(x - size, y + size, x + size, y - size, color);
}

/**
 * Vẽ nền mê cung sử dụng Bresenham Line
 */
static void drawCustomMazeBackground() {
    // Vẽ lưới mê cung
    for (int i = 0; i < SCREEN_WIDTH; i += 40) {
        bresenhamLine(i, 0, i + 20, SCREEN_HEIGHT, COLOR(20, 30, 50));
    }
    
    for (int j = 0; j < SCREEN_HEIGHT; j += 40) {
        bresenhamLine(0, j, SCREEN_WIDTH, j + 20, COLOR(20, 30, 50));
    }
}

// ============================================================
//  ÁP DỤNG THUẬT TOÁN FLOOD FILL VÀO GAME
//  Sử dụng thuật toán tô màu đệ quy đã tự cài đặt
// ============================================================

/**
 * Vẽ nhân vật với tô màu Flood Fill
 * Tô màu đầy đủ các phần của nhân vật
 */
static void drawFilledPlayer(int x, int y, bool facingRight) {
    // Đầu - vẽ viền và tô màu
    midpointCircle(x, y - 24, 8, COLOR(100, 50, 0));
    floodFill(x, y - 24, COLOR(255, 220, 180));
    
    // Thân - vẽ hình chữ nhật và tô màu
    bresenhamRectangle(x - 6, y - 16, x + 6, y - 8, COLOR(0, 100, 0));
    floodFill(x, y - 12, COLOR(40, 150, 60));
    
    // Tay trái
    int armPoints1[] = {
        x - 6, y - 14,
        x - 10, y - 10,
        x - 8, y - 8,
        x - 4, y - 12
    };
    filledPolygon(armPoints1, 4, COLOR(100, 50, 0), COLOR(255, 220, 180), x - 7, y - 11);
    
    // Tay phải
    int armPoints2[] = {
        x + 6, y - 14,
        x + 10, y - 10,
        x + 8, y - 8,
        x + 4, y - 12
    };
    filledPolygon(armPoints2, 4, COLOR(100, 50, 0), COLOR(255, 220, 180), x + 7, y - 11);
    
    // Chân trái
    int legPoints1[] = {
        x - 2, y - 8,
        x - 6, y,
        x - 4, y,
        x, y - 8
    };
    filledPolygon(legPoints1, 4, COLOR(0, 0, 100), COLOR(30, 40, 80), x - 3, y - 4);
    
    // Chân phải
    int legPoints2[] = {
        x + 2, y - 8,
        x + 6, y,
        x + 4, y,
        x, y - 8
    };
    filledPolygon(legPoints2, 4, COLOR(0, 0, 100), COLOR(30, 40, 80), x + 3, y - 4);
    
    // Mắt
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
    // Đầu - màu đỏ
    midpointCircle(x, y - 24, 8, COLOR(100, 0, 0));
    floodFill(x, y - 24, COLOR(180, 30, 30));
    
    // Thân - màu xám
    bresenhamRectangle(x - 6, y - 16, x + 6, y - 8, COLOR(50, 50, 50));
    floodFill(x, y - 12, COLOR(80, 80, 90));
    
    // Tay với vũ khí
    if (facingRight) {
        int armPoints[] = {
            x, y - 14,
            x + 8, y - 12,
            x + 8, y - 10,
            x, y - 12
        };
        filledPolygon(armPoints, 4, COLOR(100, 0, 0), COLOR(180, 30, 30), x + 4, y - 12);
        
        // Vũ khí
        filledRectangle(x + 8, y - 13, x + 14, y - 9, COLOR(100, 100, 100), COLOR(180, 180, 200));
    } else {
        int armPoints[] = {
            x, y - 14,
            x - 8, y - 12,
            x - 8, y - 10,
            x, y - 12
        };
        filledPolygon(armPoints, 4, COLOR(100, 0, 0), COLOR(180, 30, 30), x - 4, y - 12);
        
        // Vũ khí
        filledRectangle(x - 14, y - 13, x - 8, y - 9, COLOR(100, 100, 100), COLOR(180, 180, 200));
    }
    
    // Chân
    int legPoints1[] = {x - 2, y - 8, x - 6, y, x - 4, y, x, y - 8};
    filledPolygon(legPoints1, 4, COLOR(30, 30, 30), COLOR(50, 50, 60), x - 3, y - 4);
    
    int legPoints2[] = {x + 2, y - 8, x + 6, y, x + 4, y, x, y - 8};
    filledPolygon(legPoints2, 4, COLOR(30, 30, 30), COLOR(50, 50, 60), x + 3, y - 4);
    
    // Mắt phát sáng
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
    // Đầu chìa khóa - vòng tròn vàng
    midpointCircle(x, y - 8, 5, COLOR(150, 120, 0));
    floodFill(x, y - 8, COLOR(255, 215, 0));
    
    // Lỗ khóa nhỏ
    midpointCircle(x, y - 8, 2, COLOR(150, 120, 0));
    floodFill(x, y - 8, COLOR(100, 100, 0));
    
    // Thân chìa khóa
    filledRectangle(x - 1, y - 3, x + 1, y + 5, COLOR(150, 120, 0), COLOR(255, 215, 0));
    
    // Răng chìa khóa
    filledRectangle(x + 1, y - 1, x + 3, y + 1, COLOR(150, 120, 0), COLOR(255, 215, 0));
    filledRectangle(x + 1, y + 2, x + 3, y + 4, COLOR(150, 120, 0), COLOR(255, 215, 0));
}

/**
 * Vẽ cửa với tô màu Flood Fill
 */
static void drawFilledDoor(int x, int y, bool isOpen) {
    int doorColor = isOpen ? COLOR(100, 255, 100) : COLOR(139, 69, 19);
    int borderColor = isOpen ? COLOR(50, 150, 50) : COLOR(80, 40, 10);
    
    // Khung cửa
    filledRectangle(x - 12, y - 40, x + 12, y, borderColor, doorColor);
    
    if (!isOpen) {
        // Tay nắm
        midpointCircle(x + 6, y - 20, 3, COLOR(150, 120, 0));
        floodFill(x + 6, y - 20, COLOR(255, 215, 0));
        
        // Các ô trang trí
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
        // Nắp rương mở
        filledRectangle(x - 15, y - 25, x + 15, y - 20, COLOR(100, 50, 0), COLOR(139, 69, 19));
        
        // Thân rương
        filledRectangle(x - 15, y - 20, x + 15, y, COLOR(100, 50, 0), COLOR(160, 82, 45));
        
        // Vàng bên trong
        for (int i = 0; i < 5; i++) {
            int cx = x - 10 + i * 5;
            int cy = y - 15 + (i % 2) * 3;
            midpointCircle(cx, cy, 2, COLOR(150, 120, 0));
            floodFill(cx, cy, COLOR(255, 215, 0));
        }
    } else {
        // Rương đóng
        filledRectangle(x - 15, y - 20, x + 15, y, COLOR(100, 50, 0), COLOR(139, 69, 19));
        
        // Khóa
        filledRectangle(x - 3, y - 12, x + 3, y - 8, COLOR(150, 120, 0), COLOR(255, 215, 0));
    }
    
    // Viền kim loại
    bresenhamLine(x - 15, y - 10, x + 15, y - 10, COLOR(180, 180, 200));
    bresenhamLine(x, y - 20, x, y, COLOR(180, 180, 200));
}

/**
 * Vẽ cây với tô màu Flood Fill
 */
static void drawFilledTree(int x, int y) {
    // Thân cây
    filledRectangle(x - 5, y - 30, x + 5, y, COLOR(80, 40, 10), COLOR(139, 69, 19));
    
    // Tán lá (3 vòng tròn chồng lên nhau)
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
    // Tính toán 5 đỉnh ngôi sao
    int points[10];
    for (int i = 0; i < 5; i++) {
        float angle = -90 + i * 72;  // 72 độ giữa các đỉnh
        float rad = angle * M_PI / 180.0;
        points[i * 2] = x + size * cos(rad);
        points[i * 2 + 1] = y + size * sin(rad);
    }
    
    // Vẽ ngôi sao bằng cách nối các đỉnh (1-3-5-2-4-1)
    bresenhamLine(points[0], points[1], points[6], points[7], COLOR(200, 150, 0));
    bresenhamLine(points[6], points[7], points[4], points[5], COLOR(200, 150, 0));
    bresenhamLine(points[4], points[5], points[2], points[3], COLOR(200, 150, 0));
    bresenhamLine(points[2], points[3], points[8], points[9], COLOR(200, 150, 0));
    bresenhamLine(points[8], points[9], points[0], points[1], COLOR(200, 150, 0));
    
    // Tô màu
    floodFill(x, y, COLOR(255, 215, 0));
}

#endif // CUSTOM_DRAWING_H
