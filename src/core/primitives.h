#ifndef CORE_PRIMITIVES_H
#define CORE_PRIMITIVES_H

#include <graphics.h>

// ============================================================
//  Color helpers & basic filled-rect primitive
// ============================================================

// Chuyển mã màu hex 0xRRGGBB sang COLOR(r, g, b)
static int HEX2COLOR(int hexColor) {
    int r = (hexColor >> 16) & 0xFF;
    int g = (hexColor >> 8) & 0xFF;
    int b = hexColor & 0xFF;
    return COLOR(r, g, b);
}

// Vẽ hình chữ nhật đặc màu hex (theo pixel-art style)
static void drawRect(int x, int y, int w, int h, int hexColor) {
    setfillstyle(SOLID_FILL, HEX2COLOR(hexColor));
    bar(x, y, x + w, y + h);
}

// ============================================================
//  Màu nền mặc định cho các block đặc biệt
// ============================================================
// Question block màu vàng cam
static const int BG_QBLOCK    = 0xF0A020;
static const int BG_QBLOCK_DK = 0xC07010;

// Brick block màu nâu gạch
static const int BG_BRICK_BL  = 0x8C5523;

#endif // CORE_PRIMITIVES_H
