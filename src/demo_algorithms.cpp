/**
 * DEMO THUẬT TOÁN VẼ ĐƯỜNG THẲNG VÀ ĐƯỜNG TRÒN
 * 
 * File này demo các thuật toán đã tự cài đặt:
 * 1. Bresenham Line Algorithm - Vẽ đường thẳng
 * 2. Midpoint Circle Algorithm - Vẽ đường tròn
 * 3. Midpoint Ellipse Algorithm - Vẽ ellipse
 * 
 * Để chạy demo: Uncomment dòng runAlgorithmDemo() trong main.cpp
 */

#include <graphics.h>
#include <conio.h>
#include "core/algorithms.h"
#include "graphics/CustomDrawing.h"
#include "config.h"

void runAlgorithmDemo() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    
    setbkcolor(COLOR(10, 10, 30));
    cleardevice();
    
    // ============================================================
    // PHẦN 1: DEMO THUẬT TOÁN BRESENHAM LINE
    // ============================================================
    
    settextstyle(10, HORIZ_DIR, 2);
    setcolor(15);
    outtextxy(20, 10, "DEMO: BRESENHAM LINE ALGORITHM");
    
    // Vẽ các đường thẳng theo 8 hướng (8 octants)
    int centerX = 150;
    int centerY = 150;
    int lineLength = 80;
    
    setcolor(14);
    outtextxy(20, 40, "8 Octants:");
    
    // Octant 1: 0-45 độ
    bresenhamLine(centerX, centerY, centerX + lineLength, centerY - lineLength/2, COLOR(255, 0, 0));
    
    // Octant 2: 45-90 độ
    bresenhamLine(centerX, centerY, centerX + lineLength/2, centerY - lineLength, COLOR(255, 100, 0));
    
    // Octant 3: 90-135 độ
    bresenhamLine(centerX, centerY, centerX - lineLength/2, centerY - lineLength, COLOR(255, 200, 0));
    
    // Octant 4: 135-180 độ
    bresenhamLine(centerX, centerY, centerX - lineLength, centerY - lineLength/2, COLOR(0, 255, 0));
    
    // Octant 5: 180-225 độ
    bresenhamLine(centerX, centerY, centerX - lineLength, centerY + lineLength/2, COLOR(0, 255, 255));
    
    // Octant 6: 225-270 độ
    bresenhamLine(centerX, centerY, centerX - lineLength/2, centerY + lineLength, COLOR(0, 100, 255));
    
    // Octant 7: 270-315 độ
    bresenhamLine(centerX, centerY, centerX + lineLength/2, centerY + lineLength, COLOR(100, 0, 255));
    
    // Octant 8: 315-360 độ
    bresenhamLine(centerX, centerY, centerX + lineLength, centerY + lineLength/2, COLOR(255, 0, 255));
    
    // Vẽ hình chữ nhật
    setcolor(14);
    outtextxy(20, 280, "Rectangle:");
    bresenhamRectangle(50, 310, 200, 400, COLOR(255, 255, 0));
    
    // Vẽ tam giác
    setcolor(14);
    outtextxy(20, 420, "Triangle:");
    bresenhamTriangle(50, 550, 150, 450, 200, 550, COLOR(0, 255, 255));
    
    // ============================================================
    // PHẦN 2: DEMO THUẬT TOÁN MIDPOINT CIRCLE
    // ============================================================
    
    setcolor(15);
    outtextxy(350, 10, "DEMO: MIDPOINT CIRCLE ALGORITHM");
    
    setcolor(14);
    outtextxy(350, 40, "Circles with different radii:");
    
    // Vẽ các đường tròn với bán kính khác nhau
    midpointCircle(450, 120, 20, COLOR(255, 0, 0));
    midpointCircle(450, 120, 40, COLOR(255, 100, 0));
    midpointCircle(450, 120, 60, COLOR(0, 255, 0));
    midpointCircle(450, 120, 80, COLOR(0, 100, 255));
    
    // Vẽ đường tròn tô màu
    setcolor(14);
    outtextxy(350, 230, "Filled Circles:");
    
    filledMidpointCircle(400, 300, 30, COLOR(255, 50, 50));
    filledMidpointCircle(500, 300, 25, COLOR(50, 255, 50));
    filledMidpointCircle(600, 300, 35, COLOR(50, 50, 255));
    
    // ============================================================
    // PHẦN 3: DEMO THUẬT TOÁN MIDPOINT ELLIPSE
    // ============================================================
    
    setcolor(14);
    outtextxy(350, 360, "Ellipses:");
    
    midpointEllipse(450, 450, 60, 30, COLOR(255, 255, 0));
    midpointEllipse(450, 450, 30, 60, COLOR(255, 0, 255));
    midpointEllipse(550, 450, 70, 40, COLOR(0, 255, 255));
    
    // ============================================================
    // PHẦN 4: ÁP DỤNG VÀO GAME
    // ============================================================
    
    setcolor(15);
    outtextxy(750, 10, "APPLICATION IN GAME");
    
    setcolor(14);
    outtextxy(750, 40, "Custom Player:");
    drawCustomPlayer(850, 120, true, COLOR(255, 255, 255));
    drawCustomPlayer(950, 120, false, COLOR(255, 255, 255));
    
    setcolor(14);
    outtextxy(750, 150, "Custom Enemy:");
    drawCustomEnemy(850, 230, true);
    drawCustomEnemy(950, 230, false);
    
    setcolor(14);
    outtextxy(750, 260, "Bullets:");
    drawCustomBullet(820, 310, true);   // Player bullet
    drawCustomBullet(880, 310, false);  // Enemy bullet
    
    setcolor(14);
    outtextxy(750, 340, "Key:");
    drawCustomKey(820, 390);
    
    setcolor(14);
    outtextxy(750, 420, "Door (Closed/Open):");
    drawCustomDoor(820, 540, false);
    drawCustomDoor(920, 540, true);
    
    setcolor(14);
    outtextxy(750, 570, "Hearts (HP):");
    drawCustomHeart(820, 610, true);   // Filled
    drawCustomHeart(860, 610, true);
    drawCustomHeart(900, 610, false);  // Empty
    
    // Chú thích
    setcolor(11);
    settextstyle(10, HORIZ_DIR, 1);
    outtextxy(20, SCREEN_HEIGHT - 30, "Press any key to exit demo...");
    
    getch();
    closegraph();
}
