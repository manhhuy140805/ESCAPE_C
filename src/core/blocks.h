#ifndef COMPONENT_BLOCKS_H
#define COMPONENT_BLOCKS_H

#include "primitives.h"

// question block
static void drawQBlock(int x, int y, int size = 36, bool lit = true) {
    int bg   = lit ? BG_QBLOCK    : 0xA06010;
    int edge = lit ? BG_QBLOCK_DK : 0x805008;
    int hi   = lit ? 0xFFCC40     : 0xC08018;
    
    drawRect(x, y, size, size, bg);
    drawRect(x+2, y+2, size-4, size/3, hi);
    drawRect(x+2, y+size-size/5, size-4, size/5, edge);
    
    setcolor(HEX2COLOR(edge));
    setlinestyle(SOLID_LINE, 0, 2);
    rectangle(x+1, y+1, x+size-1, y+size-1);
    setlinestyle(SOLID_LINE, 0, 1);
    
    setcolor(HEX2COLOR(0xFFFFFF));
    settextstyle(DEFAULT_FONT, HORIZ_DIR, size/14);
    outtextxy(x+size/2-4, y+size/2-6, (char*)"?");
}

// brick block
static void drawBrickBlock(int x, int y, int size = 36) {
    drawRect(x, y, size, size, BG_BRICK_BL);
    drawRect(x+2, y+2, size-4, size/4, 0xD49040);
    drawRect(x+2, y+size*3/4, size-4, size/4, 0xA06018);
    drawRect(x+2, y+2, size/5, size-4, 0xD49040);
    
    setcolor(HEX2COLOR(0xB87020));
    line(x+size/2, y+2, x+size/2, y+size-2);
    line(x+2, y+size/2, x+size-2, y+size/2);
}

// terrain blocks
static void drawDirtBlock(int x, int y, int size = 36) {
    int base      = 0x5C3A21; // nền nâu đất
    int topLight  = 0x7B4A29; // lớp trên sáng hơn
    int bottomDk  = 0x3D2414; // lớp dưới đậm hơn

    // nền chính
    drawRect(x, y, size, size, base);

    // lớp highlight phía trên
    drawRect(x + 2, y + 2, size - 4, size / 4, topLight);

    // lớp tối phía dưới
    drawRect(x + 2, y + size - size / 4 - 2, size - 4, size / 4, bottomDk);

    // một vài "vệt đất" dọc cho cảm giác pixel
    setcolor(HEX2COLOR(0x3B2415));
    line(x + size / 3, y + 6,        x + size / 3, y + size - 6);
    line(x + size * 2 / 3, y + 10,   x + size * 2 / 3, y + size - 4);
}

static void drawGrassBlock(int x, int y, int size = 36) {
    // vẽ phần đất phía dưới
    drawDirtBlock(x, y, size);

    // lớp cỏ phía trên
    int grassMain   = 0x2E8B3C; // xanh lá chính
    int grassHi     = 0x5CD85C; // viền sáng
    int grassShadow = 0x1E5C2A; // bóng tối dưới mép cỏ

    int topH = size / 4;
    drawRect(x, y, size, topH + 2, grassMain);
    drawRect(x, y, size, topH / 2, grassHi);
    drawRect(x, y + topH, size, 3, grassShadow);
}

// hazard blocks
static void drawSpikeBlock(int x, int y, int size = 36) {
    // nền trong suốt
    int spikeColor = 0x33CC99; // xanh ngọc
    setcolor(HEX2COLOR(spikeColor));
    setfillstyle(SOLID_FILL, HEX2COLOR(spikeColor));

    int baseY = y + size; // chân gai ở cạnh dưới tile
    int step  = size / 4;        // mỗi gai rộng ~1/4 ô

    for (int i = 0; i < 4; ++i) {
        int left   = x + i * step;
        int right  = left + step;
        int midX   = (left + right) / 2;
        int peakY  = y + size / 2; // đỉnh nhọn

        int pts[8];
        pts[0] = left;  pts[1] = baseY;
        pts[2] = right; pts[3] = baseY;
        pts[4] = midX;  pts[5] = peakY;
        pts[6] = left;  pts[7] = baseY;
        fillpoly(4, pts);
    }
}

static void drawLavaBlock(int x, int y, int size = 36) {
    int lavaMain   = 0xFF6600; // cam đậm
    int lavaBright = 0xFFAA33; // cam sáng
    int lavaDark   = 0xCC3300; // đỏ cam đậm

    // nền dung nham
    drawRect(x, y, size, size, lavaMain);

    // lớp sáng phía trên
    drawRect(x, y, size, size / 3, lavaBright);

    // một vài "gợn sóng" tối phía dưới
    drawRect(x, y + size * 2 / 3, size, size / 6, lavaDark);
    drawRect(x, y + size * 5 / 6, size, size / 8, lavaDark);
}

// uI Button
static void drawGameButton(int x, int y, int width, int height, char* text, bool selected) {
    int x1 = x - width/2;
    int x2 = x + width/2;
    int y1 = y;
    int y2 = y + height;
    
    int btnColor = 0;

    if (selected) {
        // shadow
        drawRect(x1 + 6, y1 + 6, width, height, 0x604020);
        
        // main button
        btnColor = 0xFFCC00;
        drawRect(x1, y1, width, height, btnColor);
        
        // viền ngoài
        setcolor(HEX2COLOR(0x805020));
        setlinestyle(SOLID_LINE, 0, 4);
        rectangle(x1, y1, x2, y2);
        
        // viền trong sáng
        setcolor(HEX2COLOR(0xFFFF80));
        setlinestyle(SOLID_LINE, 0, 2);
        rectangle(x1 + 4, y1 + 4, x2 - 4, y2 - 4);
        
        // text
        setcolor(HEX2COLOR(0x402010));
    } else {
        // shadow nhạt
        drawRect(x1 + 4, y1 + 4, width, height, 0x404040);
        
        // main button
        btnColor = 0xCC9900;
        drawRect(x1, y1, width, height, btnColor);
        
        // viền ngoài
        setcolor(HEX2COLOR(0x606060));
        setlinestyle(SOLID_LINE, 0, 3);
        rectangle(x1, y1, x2, y2);
        
        // viền trong
        setcolor(HEX2COLOR(0xFFCC00));
        setlinestyle(SOLID_LINE, 0, 1);
        rectangle(x1 + 3, y1 + 3, x2 - 3, y2 - 3);
        
        // text
        setcolor(15);
    }
    
    // vẽ text căn giữa
    int oldBk = getbkcolor();
    setbkcolor(HEX2COLOR(btnColor)); // sync màu nền chữ với màu nút vàng
    
    settextstyle(10, HORIZ_DIR, 4);
    int textWidth = textwidth(text);
    int textHeight = textheight(text);
    outtextxy(x - textWidth/2, y + (height - textHeight)/2, text);
    
    setbkcolor(oldBk); // khôi phục lại bkcolor
}

// panel với viền
static void drawPanel(int x, int y, int width, int height, int bgColor, int borderColor) {
    // background
    drawRect(x, y, width, height, bgColor);
    
    // viền
    setcolor(HEX2COLOR(borderColor));
    setlinestyle(SOLID_LINE, 0, 3);
    rectangle(x, y, x + width, y + height);
}

// title với shadow effect
static void drawTextWithShadow(int x, int y, char* text, int size, int mainColor, int shadowColor) {
    settextstyle(10, HORIZ_DIR, size);
    
    int oldBk = getbkcolor();
    
    // shadow
    // lƯU Ý
    // nên chữ đổ bóng thực chất sẽ vẽ một nền hình vuông lên
    // để khắc phục tốt nhất ở BGI không có setbkmode
    // ta nên vẽ bóng lệch xa hơn 1 chút hoặc chấp nhận
    
    // tạm thời nếu game trước đây chạy ổn vì họ dùng cùng 1 bkcolor=1
    setcolor(HEX2COLOR(shadowColor));
    outtextxy(x + 5, y + 5, text);
    
    // main text
    setcolor(HEX2COLOR(mainColor));
    // để chữ main đè lên shadow mà background không tẩy chữ bóng, BGI đã bị lỗi tẩy nền
    // thực tế nếu trước đây họ không có transparancy, chữ shadow có thể chỉ là vẽ thêm
    // dù sao, ta cứ gọi lại đúng như cũ vì text background phụ thuộc vào setbkcolor trước lúc gọi hàm này
    outtextxy(x, y, text);
}

#endif // cOMPONENT_BLOCKS_H
