#ifndef ENTITY_ITEMS_H
#define ENTITY_ITEMS_H

#include <graphics.h>
#include "../config.h"

struct KeyItem {
    int x;
    int y;
    bool collected;
};

struct DoorItem {
    int x;
    int y;
    bool open;
};

static void drawKey(const KeyItem &k) {
    if (k.collected) return;
    int r = TILE_SIZE / 4;
    int cx = k.x;
    int cy = k.y - TILE_SIZE / 3;

    setcolor(GAME_COLOR_KEY);
    setfillstyle(SOLID_FILL, GAME_COLOR_KEY);

    // Vòng tròn đầu chìa
    fillellipse(cx, cy, r, r);

    // Thân chìa
    int shaftLen = TILE_SIZE / 2;
    bar(cx - 2, cy, cx + 2, cy + shaftLen);

    // Răng chìa
    bar(cx - 2, cy + shaftLen - 4, cx - r, cy + shaftLen);
    bar(cx + 2, cy + shaftLen - 4, cx + r, cy + shaftLen);
}

static void drawDoor(const DoorItem &d) {
    int w = TILE_SIZE * 2;
    int h = TILE_SIZE * 3;
    int x1 = d.x - w / 2;
    int y1 = d.y - h;
    int x2 = d.x + w / 2;
    int y2 = d.y;

    int frameColor = d.open ? GAME_COLOR_DOOR_OPEN : GAME_COLOR_DOOR_CLOSED;
    int fillColor  = d.open ? COLOR(0, 60, 0)      : COLOR(30, 30, 30);

    setfillstyle(SOLID_FILL, fillColor);
    bar(x1, y1, x2, y2);

    setcolor(frameColor);
    setlinestyle(SOLID_LINE, 0, 3);
    rectangle(x1, y1, x2, y2);

    // Tay nắm cửa
    setcolor(GAME_COLOR_KEY);
    setfillstyle(SOLID_FILL, GAME_COLOR_KEY);
    fillellipse(x2 - TILE_SIZE / 3, d.y - TILE_SIZE * 1.5, 3, 3);
}

#endif // ENTITY_ITEMS_H
