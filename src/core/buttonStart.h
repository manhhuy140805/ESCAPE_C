#ifndef BUTTON_START_H
#define BUTTON_START_H

#include <graphics.h>

// ============================================================
//  Draw Menu Button (universal - dùng cho tất cả nút)
//  x, y : tọa độ tâm button
//  selected: true = vàng, false = trắng xám
// ============================================================
static void drawMenuButton(int x, int y, int width, int height, char* text, bool selected) {
    int x1 = x - width / 2;
    int x2 = x + width / 2;
    int y1 = y - height / 2;
    int y2 = y + height / 2;

    // ── Viền ngoài trắng (khi selected) ──────────────────
    if (selected) {
        setfillstyle(SOLID_FILL, 15);
        bar(x1 - 6, y1 - 6, x2 + 6, y2 + 6);
    }

    // ── Viền xanh đậm ────────────────────────────────────
    setfillstyle(SOLID_FILL, 1);
    bar(x1 - 4, y1 - 4, x2 + 4, y2 + 4);

    // ── Nền button ───────────────────────────────────────
    if (selected) {
        // Nút được chọn - vàng
        setfillstyle(SOLID_FILL, 14);  // Vàng sáng
        bar(x1, y1, x2, y2);
        
        // Highlight trắng phía trên
        setfillstyle(SOLID_FILL, 15);
        bar(x1 + 8, y1 + 8, x2 - 8, y1 + height / 4);
        
        // Shadow nâu phía dưới
        setfillstyle(SOLID_FILL, 6);
        bar(x1 + 8, y2 - height / 5, x2 - 8, y2 - 8);
    } else {
        // Nút không chọn - trắng xám
        setfillstyle(SOLID_FILL, 15);  // Trắng
        bar(x1, y1, x2, y1 + height / 2);
        
        setfillstyle(SOLID_FILL, 7);   // Xám nhạt
        bar(x1, y1 + height / 2, x2, y2);
        
        // Highlight
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
        setbkcolor(14);  // Nền chữ trùng màu nút vàng
    } else {
        setbkcolor(15);  // Nền chữ trùng màu trắng/xám nhạt
    }

    settextstyle(10, HORIZ_DIR, 4);
    int tw = textwidth(text);
    int th = textheight(text);
    int tx = x - tw / 2;
    int ty = y - th / 2;

    // Shadow
    if (selected) {
        setcolor(6);  // Shadow nâu cho nút vàng
    } else {
        setcolor(8);  // Shadow xám cho nút trắng
    }
    outtextxy(tx + 2, ty + 2, text);

    // Text chính
    setcolor(0);
    outtextxy(tx, ty, text);

    // Khôi phục màu nền chữ ban đầu
    setbkcolor(oldBk);
}

// Alias cho các nút khác nhau (giờ đều dùng chung)
static void drawStartButton(int x, int y, int width, int height, bool selected) {
    char label[] = "START  GAME";
    drawMenuButton(x, y, width, height, label, selected);
}

// ============================================================
//  Draw INSTRUCTIONS Button
// ============================================================
static void drawInstructionsButton(int x, int y, int width = 460, int height = 80, bool selected = false) {
    char label[] = "INSTRUCTIONS";
    drawMenuButton(x, y, width, height, label, selected);
}

// ============================================================
//  Draw EXIT Button
// ============================================================
static void drawExitButton(int x, int y, int width = 460, int height = 80, bool selected = false) {
    char label[] = "EXIT";
    drawMenuButton(x, y, width, height, label, selected);
}

#endif
