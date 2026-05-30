#ifndef CORE_PRIMITIVES_H
#define CORE_PRIMITIVES_H

#include <graphics.h>

// color helpers & basic filled

// chuyển mã màu hex 0xRRGGBB sang COLOR
static int HEX2COLOR(int hexColor) {
    int r = (hexColor >> 16) & 0xFF;
    int g = (hexColor >> 8) & 0xFF;
    int b = hexColor & 0xFF;
    return COLOR(r, g, b);
}

// vẽ hình chữ nhật đặc màu hex
static void drawRect(int x, int y, int w, int h, int hexColor) {
    setfillstyle(SOLID_FILL, HEX2COLOR(hexColor));
    bar(x, y, x + w, y + h);
}

// màu nền mặc định cho các block đặc biệt
// question block màu vàng cam
static const int BG_QBLOCK    = 0xF0A020;
static const int BG_QBLOCK_DK = 0xC07010;

// brick block màu nâu gạch
static const int BG_BRICK_BL  = 0x8C5523;

#endif // cORE_PRIMITIVES_H
