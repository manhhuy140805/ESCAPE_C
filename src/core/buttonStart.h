#ifndef BUTTON_START_H
#define BUTTON_START_H

#include <graphics.h>

// draw Menu Button
static void drawMenuButton(int x, int y, int width, int height, char* text, bool selected) {
    int x1 = x - width / 2;
    int x2 = x + width / 2;
    int y1 = y - height / 2;
    int y2 = y + height / 2;

    // ── Viền ngoài trắng
    if (selected) {
        setfillstyle(SOLID_FILL, 15);
        bar(x1 - 6, y1 - 6, x2 + 6, y2 + 6);
    }

    // ── Viền xanh đậm ────────────────────────────────────
    setfillstyle(SOLID_FILL, 1);
    bar(x1 - 4, y1 - 4, x2 + 4, y2 + 4);

    // ── Nền button ───────────────────────────────────────
    if (selected) {
        // nút được chọn
        setfillstyle(SOLID_FILL, 14); // vàng sáng
        bar(x1, y1, x2, y2);
        
        // highlight trắng phía trên
        setfillstyle(SOLID_FILL, 15);
        bar(x1 + 8, y1 + 8, x2 - 8, y1 + height / 4);
        
        // shadow nâu phía dưới
        setfillstyle(SOLID_FILL, 6);
        bar(x1 + 8, y2 - height / 5, x2 - 8, y2 - 8);
    } else {
        // nút không chọn
        setfillstyle(SOLID_FILL, 15); // trắng
        bar(x1, y1, x2, y1 + height / 2);
        
        setfillstyle(SOLID_FILL, 7); // xám nhạt
        bar(x1, y1 + height / 2, x2, y2);
        
        // highlight
        setfillstyle(SOLID_FILL, 15);
        bar(x1 + 8, y1 + 8, x2 - 8, y1 + height / 5);
    }

    // ── Viền button ──────────────────────────────────────
    setcolor(0);
    setlinestyle(SOLID_LINE, 0, 3);
    rectangle(x1, y1, x2, y2);

    // ── Text ─────────────────────────────────────────────
    int oldBk = getbkcolor();
    if (selected) {
        setbkcolor(14); // nền chữ trùng màu nút vàng
    } else {
        setbkcolor(15); // nền chữ trùng màu trắng/xám nhạt
    }

    settextstyle(10, HORIZ_DIR, 4);
    int tw = textwidth(text);
    int th = textheight(text);
    int tx = x - tw / 2;
    int ty = y - th / 2;

    // shadow
    if (selected) {
        setcolor(6); // shadow nâu cho nút vàng
    } else {
        setcolor(8); // shadow xám cho nút trắng
    }
    outtextxy(tx + 2, ty + 2, text);

    // text chính
    setcolor(0);
    outtextxy(tx, ty, text);

    // khôi phục màu nền chữ ban đầu
    setbkcolor(oldBk);
}

// alias cho các nút khác nhau
static void drawStartButton(int x, int y, int width, int height, bool selected) {
    char label[] = "START  GAME";
    drawMenuButton(x, y, width, height, label, selected);
}

// draw INSTRUCTIONS Button
static void drawInstructionsButton(int x, int y, int width = 460, int height = 80, bool selected = false) {
    char label[] = "INSTRUCTIONS";
    drawMenuButton(x, y, width, height, label, selected);
}

// draw EXIT Button
static void drawExitButton(int x, int y, int width = 460, int height = 80, bool selected = false) {
    char label[] = "EXIT";
    drawMenuButton(x, y, width, height, label, selected);
}

#endif
