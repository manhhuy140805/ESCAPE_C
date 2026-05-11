#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <graphics.h>
#include <cmath>

// Hằng số PI
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// thuật toán bresenham vẽ đường thẳng
static void bresenhamLine(int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int x = x1, y = y1;
    
    setcolor(color);
    
    // trường hợp 1: độ dốc nhỏ (|dy| <= |dx|)
    if (dx >= dy) {
        int p = 2 * dy - dx;
        for (int i = 0; i <= dx; i++) {
            putpixel(x, y, color);
            if (p >= 0) {
                y += sy;
                p += 2 * (dy - dx);
            } else {
                p += 2 * dy;
            }
            x += sx;
        }
    }
    // trường hợp 2: độ dốc lớn (|dy| > |dx|)
    else {
        int p = 2 * dx - dy;
        for (int i = 0; i <= dy; i++) {
            putpixel(x, y, color);
            if (p >= 0) {
                x += sx;
                p += 2 * (dx - dy);
            } else {
                p += 2 * dx;
            }
            y += sy;
        }
    }
}

// vẽ 8 điểm đối xứng của đường tròn
static void plot8CirclePoints(int xc, int yc, int x, int y, int color) {
    putpixel(xc + x, yc + y, color);
    putpixel(xc - x, yc + y, color);
    putpixel(xc + x, yc - y, color);
    putpixel(xc - x, yc - y, color);
    putpixel(xc + y, yc + x, color);
    putpixel(xc - y, yc + x, color);
    putpixel(xc + y, yc - x, color);
    putpixel(xc - y, yc - x, color);
}

// thuật toán midpoint circle vẽ đường tròn
static void midpointCircle(int xc, int yc, int radius, int color) {
    int x = 0;
    int y = radius;
    int p = 1 - radius;
    
    setcolor(color);
    plot8CirclePoints(xc, yc, x, y, color);
    
    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        plot8CirclePoints(xc, yc, x, y, color);
    }
}

// vẽ 4 điểm đối xứng của ellipse
static void plot4EllipsePoints(int xc, int yc, int x, int y, int color) {
    putpixel(xc + x, yc + y, color);
    putpixel(xc - x, yc + y, color);
    putpixel(xc + x, yc - y, color);
    putpixel(xc - x, yc - y, color);
}

// thuật toán midpoint ellipse vẽ ellipse
static void midpointEllipse(int xc, int yc, int rx, int ry, int color) {
    int x = 0, y = ry;
    int rx2 = rx * rx, ry2 = ry * ry;
    int twoRx2 = 2 * rx2, twoRy2 = 2 * ry2;
    
    setcolor(color);
    
    // vùng 1: độ dốc < 1
    int px = 0, py = twoRx2 * y;
    int p1 = ry2 - (rx2 * ry) + (0.25 * rx2);
    plot4EllipsePoints(xc, yc, x, y, color);
    
    while (px < py) {
        x++;
        px += twoRy2;
        if (p1 < 0) {
            p1 += ry2 + px;
        } else {
            y--;
            py -= twoRx2;
            p1 += ry2 + px - py;
        }
        plot4EllipsePoints(xc, yc, x, y, color);
    }
    
    // vùng 2: độ dốc >= 1
    int p2 = ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;
    while (y > 0) {
        y--;
        py -= twoRx2;
        if (p2 > 0) {
            p2 += rx2 - py;
        } else {
            x++;
            px += twoRy2;
            p2 += rx2 - py + px;
        }
        plot4EllipsePoints(xc, yc, x, y, color);
    }
}

// vẽ hình chữ nhật bằng bresenham line
static void bresenhamRectangle(int x1, int y1, int x2, int y2, int color) {
    bresenhamLine(x1, y1, x2, y1, color);
    bresenhamLine(x2, y1, x2, y2, color);
    bresenhamLine(x2, y2, x1, y2, color);
    bresenhamLine(x1, y2, x1, y1, color);
}

// vẽ tam giác bằng bresenham line
static void bresenhamTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color) {
    bresenhamLine(x1, y1, x2, y2, color);
    bresenhamLine(x2, y2, x3, y3, color);
    bresenhamLine(x3, y3, x1, y1, color);
}

// vẽ đường tròn tô màu bằng midpoint circle
static void filledMidpointCircle(int xc, int yc, int radius, int color) {
    int x = 0, y = radius;
    int p = 1 - radius;
    
    setcolor(color);
    bresenhamLine(xc - radius, yc, xc + radius, yc, color);
    
    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        bresenhamLine(xc - x, yc + y, xc + x, yc + y, color);
        bresenhamLine(xc - x, yc - y, xc + x, yc - y, color);
        bresenhamLine(xc - y, yc + x, xc + y, yc + x, color);
        bresenhamLine(xc - y, yc - x, xc + y, yc - x, color);
    }
}

// ============================================================================
// THUẬT TOÁN TÔ MÀU ĐA GIÁC ĐỆ QUY (FLOOD FILL)
// ============================================================================

/**
 * Thuật toán Flood Fill đệ quy - Tô màu vùng kín
 * 
 * Nguyên lý:
 * 1. Bắt đầu từ điểm seed (x, y)
 * 2. Kiểm tra màu hiện tại tại điểm đó
 * 3. Nếu màu hiện tại == màu cũ (oldColor) và != màu mới (fillColor):
 *    - Tô điểm hiện tại bằng màu mới
 *    - Đệ quy sang 4 điểm lân cận (trên, dưới, trái, phải)
 * 4. Dừng khi gặp biên (màu khác oldColor) hoặc đã tô (màu == fillColor)
 * 
 * Ưu điểm: Đơn giản, dễ hiểu, tô chính xác vùng kín
 * Nhược điểm: Có thể gây stack overflow với vùng lớn
 * 
 * @param x, y: Tọa độ điểm bắt đầu (seed point)
 * @param fillColor: Màu tô mới
 * @param oldColor: Màu cũ cần thay thế
 */
static void floodFillRecursive(int x, int y, int fillColor, int oldColor) {
    // Điều kiện dừng: nằm ngoài màn hình
    if (x < 0 || x >= getmaxx() || y < 0 || y >= getmaxy()) {
        return;
    }
    
    // Lấy màu hiện tại tại điểm (x, y)
    int currentColor = getpixel(x, y);
    
    // Điều kiện dừng: màu hiện tại không phải màu cũ hoặc đã được tô
    if (currentColor != oldColor || currentColor == fillColor) {
        return;
    }
    
    // Tô điểm hiện tại
    putpixel(x, y, fillColor);
    
    // Đệ quy sang 4 điểm lân cận (4-connected)
    floodFillRecursive(x + 1, y, fillColor, oldColor); // Phải
    floodFillRecursive(x - 1, y, fillColor, oldColor); // Trái
    floodFillRecursive(x, y + 1, fillColor, oldColor); // Dưới
    floodFillRecursive(x, y - 1, fillColor, oldColor); // Trên
}

/**
 * Hàm wrapper cho Flood Fill - Tự động lấy màu cũ
 * 
 * @param x, y: Tọa độ điểm bắt đầu
 * @param fillColor: Màu tô mới
 */
static void floodFill(int x, int y, int fillColor) {
    // Kiểm tra tọa độ hợp lệ
    if (x < 0 || x >= getmaxx() || y < 0 || y >= getmaxy()) {
        return;
    }
    
    // Lấy màu cũ tại điểm seed
    int oldColor = getpixel(x, y);
    
    // Nếu màu cũ == màu mới thì không cần tô
    if (oldColor == fillColor) {
        return;
    }
    
    // Gọi hàm đệ quy
    floodFillRecursive(x, y, fillColor, oldColor);
}

/**
 * Flood Fill 8-connected (tô cả 8 hướng kể cả đường chéo)
 * 
 * Khác với 4-connected, thuật toán này tô cả 8 điểm lân cận:
 * - 4 điểm trực tiếp (trên, dưới, trái, phải)
 * - 4 điểm chéo (trên-trái, trên-phải, dưới-trái, dưới-phải)
 * 
 * @param x, y: Tọa độ điểm bắt đầu
 * @param fillColor: Màu tô mới
 * @param oldColor: Màu cũ cần thay thế
 */
static void floodFill8Recursive(int x, int y, int fillColor, int oldColor) {
    // Điều kiện dừng: nằm ngoài màn hình
    if (x < 0 || x >= getmaxx() || y < 0 || y >= getmaxy()) {
        return;
    }
    
    // Lấy màu hiện tại
    int currentColor = getpixel(x, y);
    
    // Điều kiện dừng
    if (currentColor != oldColor || currentColor == fillColor) {
        return;
    }
    
    // Tô điểm hiện tại
    putpixel(x, y, fillColor);
    
    // Đệ quy sang 8 điểm lân cận (8-connected)
    floodFill8Recursive(x + 1, y, fillColor, oldColor);     // Phải
    floodFill8Recursive(x - 1, y, fillColor, oldColor);     // Trái
    floodFill8Recursive(x, y + 1, fillColor, oldColor);     // Dưới
    floodFill8Recursive(x, y - 1, fillColor, oldColor);     // Trên
    floodFill8Recursive(x + 1, y + 1, fillColor, oldColor); // Phải-Dưới
    floodFill8Recursive(x + 1, y - 1, fillColor, oldColor); // Phải-Trên
    floodFill8Recursive(x - 1, y + 1, fillColor, oldColor); // Trái-Dưới
    floodFill8Recursive(x - 1, y - 1, fillColor, oldColor); // Trái-Trên
}

/**
 * Hàm wrapper cho Flood Fill 8-connected
 */
static void floodFill8(int x, int y, int fillColor) {
    if (x < 0 || x >= getmaxx() || y < 0 || y >= getmaxy()) {
        return;
    }
    
    int oldColor = getpixel(x, y);
    
    if (oldColor == fillColor) {
        return;
    }
    
    floodFill8Recursive(x, y, fillColor, oldColor);
}

/**
 * Tô màu hình chữ nhật (sử dụng flood fill)
 * 
 * @param x1, y1: Góc trên trái
 * @param x2, y2: Góc dưới phải
 * @param borderColor: Màu viền
 * @param fillColor: Màu tô
 */
static void filledRectangle(int x1, int y1, int x2, int y2, int borderColor, int fillColor) {
    // Vẽ viền
    bresenhamRectangle(x1, y1, x2, y2, borderColor);
    
    // Tô màu bên trong (điểm seed ở giữa hình chữ nhật)
    int centerX = (x1 + x2) / 2;
    int centerY = (y1 + y2) / 2;
    floodFill(centerX, centerY, fillColor);
}

/**
 * Tô màu tam giác (sử dụng flood fill)
 * 
 * @param x1, y1, x2, y2, x3, y3: 3 đỉnh tam giác
 * @param borderColor: Màu viền
 * @param fillColor: Màu tô
 */
static void filledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int borderColor, int fillColor) {
    // Vẽ viền
    bresenhamTriangle(x1, y1, x2, y2, x3, y3, borderColor);
    
    // Tô màu bên trong (điểm seed ở trọng tâm tam giác)
    int centerX = (x1 + x2 + x3) / 3;
    int centerY = (y1 + y2 + y3) / 3;
    floodFill(centerX, centerY, fillColor);
}

/**
 * Tô màu đa giác bất kỳ (sử dụng flood fill)
 * 
 * @param points: Mảng các điểm đỉnh (x1, y1, x2, y2, ...)
 * @param numPoints: Số lượng đỉnh
 * @param borderColor: Màu viền
 * @param fillColor: Màu tô
 * @param seedX, seedY: Điểm seed để bắt đầu tô (phải nằm trong đa giác)
 */
static void filledPolygon(int points[], int numPoints, int borderColor, int fillColor, int seedX, int seedY) {
    // Vẽ viền đa giác
    for (int i = 0; i < numPoints - 1; i++) {
        bresenhamLine(points[i * 2], points[i * 2 + 1], 
                     points[(i + 1) * 2], points[(i + 1) * 2 + 1], 
                     borderColor);
    }
    // Đóng đa giác (nối điểm cuối với điểm đầu)
    bresenhamLine(points[(numPoints - 1) * 2], points[(numPoints - 1) * 2 + 1],
                 points[0], points[1], 
                 borderColor);
    
    // Tô màu bên trong
    floodFill(seedX, seedY, fillColor);
}

#endif // ALGORITHMS_H
