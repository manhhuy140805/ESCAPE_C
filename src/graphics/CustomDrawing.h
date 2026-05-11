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

#endif // CUSTOM_DRAWING_H
