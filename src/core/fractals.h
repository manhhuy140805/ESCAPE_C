#ifndef CORE_FRACTALS_H
#define CORE_FRACTALS_H

#include <math.h>
#include "../config.h"
#include "algorithms.h"

// hINH HOC FRACTAL

static void drawKochCurve(int x1, int y1, int x2, int y2, int depth, int color) {
    if (depth <= 0) {
        bresenhamLine(x1, y1, x2, y2, color);
        return;
    }

    int dx = x2 - x1;
    int dy = y2 - y1;

    int ax = x1 + dx / 3;
    int ay = y1 + dy / 3;
    int bx = x1 + 2 * dx / 3;
    int by = y1 + 2 * dy / 3;

    float angle = -60.0f * (float)M_PI / 180.0f;
    int px = ax + (int)((bx - ax) * cos(angle) - (by - ay) * sin(angle));
    int py = ay + (int)((bx - ax) * sin(angle) + (by - ay) * cos(angle));

    drawKochCurve(x1, y1, ax, ay, depth - 1, color);
    drawKochCurve(ax, ay, px, py, depth - 1, color);
    drawKochCurve(px, py, bx, by, depth - 1, color);
    drawKochCurve(bx, by, x2, y2, depth - 1, color);
}

static void drawDragonCurve(int x1, int y1, int x2, int y2, int depth, int sign, int color) {
    if (depth <= 0) {
        bresenhamLine(x1, y1, x2, y2, color);
        return;
    }

    int mx = (x1 + x2) / 2 + sign * (y2 - y1) / 2;
    int my = (y1 + y2) / 2 - sign * (x2 - x1) / 2;

    drawDragonCurve(x1, y1, mx, my, depth - 1, 1, color);
    drawDragonCurve(x2, y2, mx, my, depth - 1, -1, color);
}

static void drawFractalTree(int x1, int y1, float length, float angleDeg, int depth) {
    if (depth <= 0 || length < 3.0f) return;

    float rad = angleDeg * (float)M_PI / 180.0f;
    int x2 = x1 + (int)(cos(rad) * length);
    int y2 = y1 - (int)(sin(rad) * length);

    int trunkColor = depth > 3 ? COLOR(95, 58, 24) : COLOR(34, 150, 62);
    bresenhamLine(x1, y1, x2, y2, trunkColor);

    drawFractalTree(x2, y2, length * 0.68f, angleDeg + 28.0f, depth - 1);
    drawFractalTree(x2, y2, length * 0.68f, angleDeg - 28.0f, depth - 1);
}

static void drawKochSnowflake(int cx, int cy, int size, int depth, int color) {
    // bong tuyet 6 canh
    for (int i = 0; i < 6; ++i) {
        float angle = (-90.0f + i * 60.0f) * (float)M_PI / 180.0f;
        int ex = cx + (int)(cos(angle) * size);
        int ey = cy + (int)(sin(angle) * size);
        drawKochCurve(cx, cy, ex, ey, depth, color);

        // hai nhanh phu ngan tao dang tinh the tuyet
        float sideA = angle + 35.0f * (float)M_PI / 180.0f;
        float sideB = angle - 35.0f * (float)M_PI / 180.0f;
        int bx = cx + (int)(cos(angle) * size * 0.55f);
        int by = cy + (int)(sin(angle) * size * 0.55f);
        int ax = bx + (int)(cos(sideA) * size * 0.22f);
        int ay = by + (int)(sin(sideA) * size * 0.22f);
        int dx = bx + (int)(cos(sideB) * size * 0.22f);
        int dy = by + (int)(sin(sideB) * size * 0.22f);
        bresenhamLine(bx, by, ax, ay, color);
        bresenhamLine(bx, by, dx, dy, color);
    }
}

#endif // cORE_FRACTALS_H
