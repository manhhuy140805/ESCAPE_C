#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <graphics.h>
#include <cmath>

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

#endif // ALGORITHMS_H
