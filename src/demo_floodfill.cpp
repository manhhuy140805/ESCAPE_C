/**
 * DEMO THUẬT TOÁN FLOOD FILL - TÔ MÀU ĐA GIÁC ĐỆ QUY
 * 
 * File này demo các thuật toán tô màu đa giác:
 * 1. Flood Fill 4-connected (tô 4 hướng)
 * 2. Flood Fill 8-connected (tô 8 hướng)
 * 3. Tô hình chữ nhật
 * 4. Tô tam giác
 * 5. Tô đa giác bất kỳ
 * 
 * Cách chạy:
 * 1. Uncomment dòng runFloodFillDemo() trong main.cpp
 * 2. Build: ./build.bat
 * 3. Run: ./game.exe
 */

#include <graphics.h>
#include <conio.h>
#include "core/algorithms.h"
#include "config.h"

/**
 * Demo 1: Flood Fill 4-connected vs 8-connected
 */
static void demoFloodFillComparison() {
    cleardevice();
    
    // tiêu đề
    setcolor(WHITE);
    outtextxy(400, 20, (char*)"DEMO: FLOOD FILL 4-CONNECTED VS 8-CONNECTED");
    outtextxy(200, 50, (char*)"4-Connected (Trai)");
    outtextxy(650, 50, (char*)"8-Connected (Phai)");
    
    // vẽ 2 hình chữ nhật giống nhau
    // hình 1
    bresenhamRectangle(100, 100, 300, 250, WHITE);
    outtextxy(150, 270, (char*)"4 huong");
    
    // hình 2
    bresenhamRectangle(550, 100, 750, 250, WHITE);
    outtextxy(600, 270, (char*)"8 huong");
    
    // tô màu
    floodFill(200, 175, BLUE); // 4
    floodFill8(650, 175, GREEN); // 8
    
    outtextxy(300, 750, (char*)"Nhan phim bat ky de tiep tuc...");
    getch();
}

/**
 * Demo 2: Tô các hình cơ bản
 */
static void demoBasicShapes() {
    cleardevice();
    
    setcolor(WHITE);
    outtextxy(350, 20, (char*)"DEMO: TO MAU CAC HINH CO BAN");
    
    // hình chữ nhật
    outtextxy(150, 80, (char*)"Hinh chu nhat");
    filledRectangle(100, 100, 250, 200, WHITE, RED);
    
    // tam giác
    outtextxy(400, 80, (char*)"Tam giac");
    filledTriangle(450, 100, 400, 200, 500, 200, WHITE, YELLOW);
    
    // hình tròn
    outtextxy(650, 80, (char*)"Hinh tron");
    midpointCircle(700, 150, 50, WHITE);
    floodFill(700, 150, CYAN);
    
    // ellipse
    outtextxy(150, 280, (char*)"Ellipse");
    midpointEllipse(175, 380, 60, 40, WHITE);
    floodFill(175, 380, MAGENTA);
    
    // ngũ giác
    outtextxy(400, 280, (char*)"Ngu giac");
    int pentagon[] = {
        450, 300, // đỉnh 1
        490, 340, // đỉnh 2
        470, 390, // đỉnh 3
        430, 390, // đỉnh 4
        410, 340 // đỉnh 5
    };
    filledPolygon(pentagon, 5, WHITE, GREEN, 450, 360);
    
    // ngôi sao 5 cánh
    outtextxy(650, 280, (char*)"Ngoi sao");
    int star[] = {
        700, 300, // đỉnh trên
        710, 340, // phải trên
        750, 340, // phải xa
        720, 365, // phải dưới
        730, 400, // phải xa dưới
        700, 380, // dưới
        670, 400, // trái xa dưới
        680, 365, // trái dưới
        650, 340, // trái xa
        690, 340 // trái trên
    };
    filledPolygon(star, 10, YELLOW, YELLOW, 700, 355);
    
    outtextxy(300, 750, (char*)"Nhan phim bat ky de tiep tuc...");
    getch();
}

/**
 * Demo 3: Tô màu phức tạp - Vẽ nhà
 */
static void demoComplexShape() {
    cleardevice();
    
    setcolor(WHITE);
    outtextxy(400, 20, (char*)"DEMO: TO MAU HINH PHUC TAP - VE NHA");
    
    int centerX = 550;
    int centerY = 400;
    
    // mái nhà
    filledTriangle(
        centerX, centerY - 100, // đỉnh
        centerX - 120, centerY, // trái
        centerX + 120, centerY, // phải
        WHITE, RED
    );
    
    // thân nhà
    filledRectangle(
        centerX - 100, centerY,
        centerX + 100, centerY + 150,
        WHITE, YELLOW
    );
    
    // cửa
    filledRectangle(
        centerX - 30, centerY + 70,
        centerX + 30, centerY + 150,
        WHITE, BROWN
    );
    
    // cửa sổ trái
    filledRectangle(
        centerX - 80, centerY + 30,
        centerX - 40, centerY + 70,
        WHITE, CYAN
    );
    
    // cửa sổ phải
    filledRectangle(
        centerX + 40, centerY + 30,
        centerX + 80, centerY + 70,
        WHITE, CYAN
    );
    
    // khung cửa sổ
    bresenhamLine(centerX - 60, centerY + 30, centerX - 60, centerY + 70, WHITE);
    bresenhamLine(centerX - 80, centerY + 50, centerX - 40, centerY + 50, WHITE);
    
    bresenhamLine(centerX + 60, centerY + 30, centerX + 60, centerY + 70, WHITE);
    bresenhamLine(centerX + 40, centerY + 50, centerX + 80, centerY + 50, WHITE);
    
    // ống khói
    filledRectangle(
        centerX + 50, centerY - 80,
        centerX + 70, centerY - 40,
        WHITE, DARKGRAY
    );
    
    // khói
    midpointCircle(centerX + 60, centerY - 90, 8, LIGHTGRAY);
    floodFill(centerX + 60, centerY - 90, LIGHTGRAY);
    
    midpointCircle(centerX + 70, centerY - 105, 10, LIGHTGRAY);
    floodFill(centerX + 70, centerY - 105, LIGHTGRAY);
    
    midpointCircle(centerX + 55, centerY - 120, 12, LIGHTGRAY);
    floodFill(centerX + 55, centerY - 120, LIGHTGRAY);
    
    // mặt trời
    midpointCircle(150, 150, 40, YELLOW);
    floodFill(150, 150, YELLOW);
    
    // tia nắng
    for (int i = 0; i < 8; i++) {
        float angle = i * 45 * M_PI / 180;
        int x1 = 150 + 50 * cos(angle);
        int y1 = 150 + 50 * sin(angle);
        int x2 = 150 + 70 * cos(angle);
        int y2 = 150 + 70 * sin(angle);
        bresenhamLine(x1, y1, x2, y2, YELLOW);
    }
    
    // cỏ
    for (int i = 0; i < 10; i++) {
        int x = 350 + i * 40;
        filledTriangle(x, 550, x - 10, 570, x + 10, 570, WHITE, GREEN);
    }
    
    outtextxy(300, 750, (char*)"Nhan phim bat ky de tiep tuc...");
    getch();
}

/**
 * Demo 4: Interactive - Người dùng click để tô màu
 */
static void demoInteractive() {
    cleardevice();
    
    setcolor(WHITE);
    outtextxy(300, 20, (char*)"DEMO: INTERACTIVE - CLICK DE TO MAU");
    outtextxy(200, 50, (char*)"Click vao ben trong cac hinh de to mau");
    outtextxy(200, 70, (char*)"Nhan ESC de thoat");
    
    // vẽ các hình chỉ có viền
    bresenhamRectangle(100, 120, 250, 220, WHITE);
    outtextxy(130, 230, (char*)"Hinh 1");
    
    bresenhamTriangle(350, 120, 300, 220, 400, 220, WHITE);
    outtextxy(330, 230, (char*)"Hinh 2");
    
    midpointCircle(550, 170, 50, WHITE);
    outtextxy(530, 230, (char*)"Hinh 3");
    
    midpointEllipse(700, 170, 60, 40, WHITE);
    outtextxy(680, 230, (char*)"Hinh 4");
    
    int pentagon[] = {200, 300, 240, 340, 220, 390, 180, 390, 160, 340};
    filledPolygon(pentagon, 5, WHITE, BLACK, -1, -1); // chỉ vẽ viền
    outtextxy(180, 400, (char*)"Hinh 5");
    
    // vẽ bảng màu
    outtextxy(400, 280, (char*)"Bang mau:");
    int colors[] = {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE};
    const char* colorNames[] = {"RED", "GREEN", "BLUE", "YELLOW", "CYAN", "MAGENTA", "WHITE"};
    
    for (int i = 0; i < 7; i++) {
        filledRectangle(400 + i * 80, 310, 470 + i * 80, 340, WHITE, colors[i]);
        outtextxy(405 + i * 80, 345, (char*)colorNames[i]);
    }
    
    outtextxy(200, 450, (char*)"Huong dan:");
    outtextxy(200, 470, (char*)"1. Click vao mau trong bang mau");
    outtextxy(200, 490, (char*)"2. Click vao ben trong hinh de to mau do");
    outtextxy(200, 510, (char*)"3. Thu voi cac hinh khac nhau!");
    
    // chế độ interactive
    outtextxy(200, 600, (char*)"[Demo mode - Nhan phim bat ky de xem ket qua mau]");
    getch();
    
    // tô màu mẫu
    floodFill(175, 170, RED);
    floodFill(350, 170, GREEN);
    floodFill(550, 170, BLUE);
    floodFill(700, 170, YELLOW);
    floodFill(200, 350, CYAN);
    
    outtextxy(300, 750, (char*)"Nhan phim bat ky de thoat...");
    getch();
}

/**
 * Hàm chính chạy tất cả demo
 */
void runFloodFillDemo() {
    // khởi tạo graphics
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
    
    // chạy các demo
    demoFloodFillComparison();
    demoBasicShapes();
    demoComplexShape();
    demoInteractive();
    
    closegraph();
}
