#include "Menu.h"
#include "../config.h"
#include "../core/buttonStart.h"
#include "../core/decorations.h"
#include <conio.h>

Menu::Menu() {
    selectedOption = 0;
    totalOptions = 3;
    lastKey = 0;
}

void Menu::drawBackground() {
    // vẽ background mê cung
    drawLabyrinthBackground();
    
    // vẽ các ngôi sao trang trí
    drawStars();
}

void Menu::drawTitle() {
    // vẽ title với outline đẹp
    drawGameTitle(SCREEN_WIDTH/2 - 320, 80);
}

void Menu::drawOptions() {
    int centerX = SCREEN_WIDTH / 2;
    int startY = 300;
    int spacing = 110;
    
    // sTART GAME button
    drawStartButton(centerX, startY, 460, 80, selectedOption == 0);
    
    // iNSTRUCTIONS button
    drawInstructionsButton(centerX, startY + spacing, 460, 80, selectedOption == 1);
    
    // eXIT button
    drawExitButton(centerX, startY + spacing * 2, 460, 80, selectedOption == 2);
    
    // hướng dẫn
    settextstyle(8, HORIZ_DIR, 2);
    setcolor(15);
    char hint[] = "UP/DOWN: Select  |  ENTER: Confirm";
    outtextxy(SCREEN_WIDTH/2 - 220, 680, hint);
}

void Menu::drawInstructions() {
    // background
    drawLabyrinthBackground();
    drawStars();
    
    // tITLE với shadow
    // shadow
    settextstyle(10, HORIZ_DIR, 5);
    setcolor(COLOR(0, 0, 0));
    char title[] = "HOW TO PLAY";
    outtextxy(SCREEN_WIDTH/2 - 218, 42, title);
    
    // main title
    setcolor(COLOR(255, 200, 0));
    outtextxy(SCREEN_WIDTH/2 - 220, 40, title);
    
    // underline
    for (int i = 0; i < 3; i++) {
        setcolor(COLOR(255, 200 - i*20, 0));
        line(SCREEN_WIDTH/2 - 230, 95 + i, SCREEN_WIDTH/2 + 230, 95 + i);
    }
    
    // bEAUTIFUL PANELS
    
    auto drawBeautifulPanel = [](int x1, int y1, int x2, int y2) {
        // shadow
        setfillstyle(SOLID_FILL, COLOR(0, 0, 0));
        bar(x1 + 5, y1 + 5, x2 + 5, y2 + 5);
        
        // main panel
        for (int i = 0; i < 5; i++) {
            setfillstyle(SOLID_FILL, COLOR(80 - i*3, 130 - i*3, 180 - i*3));
            bar(x1 + i, y1 + i, x2 - i, y2 - i);
        }
        
        // inner fill
        setfillstyle(SOLID_FILL, COLOR(100, 150, 200));
        bar(x1 + 5, y1 + 5, x2 - 5, y2 - 5);
        
        // border
        setcolor(COLOR(60, 100, 150));
        rectangle(x1, y1, x2, y2);
        setcolor(COLOR(80, 120, 170));
        rectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
    };
    
    // panels
    drawBeautifulPanel(60, 120, 520, 360);
    drawBeautifulPanel(60, 380, 520, 540);
    drawBeautifulPanel(540, 120, 1040, 390);
    drawBeautifulPanel(540, 410, 1040, 570);
    drawBeautifulPanel(80, 590, 1020, 660);
    
    settextstyle(8, HORIZ_DIR, 2);
    
    int col1X = 80;
    int col2X = 560;
    
    // cONTROLS
    setcolor(COLOR(150, 220, 255));
    settextstyle(10, HORIZ_DIR, 3);
    char ctrl[] = "CONTROLS";
    outtextxy(col1X, 130, ctrl);
    
    setcolor(COLOR(150, 220, 255));
    line(col1X, 160, col1X + 150, 160);
    
    settextstyle(8, HORIZ_DIR, 2);
    
    // keys
    setcolor(COLOR(255, 255, 255));
    char c1[] = "W / SPACE";
    outtextxy(col1X + 20, 180, c1);
    setcolor(COLOR(150, 200, 255));
    char c1d[] = "Jump";
    outtextxy(col1X + 200, 180, c1d);
    
    setcolor(COLOR(255, 255, 255));
    char c2[] = "A";
    outtextxy(col1X + 20, 210, c2);
    setcolor(COLOR(150, 200, 255));
    char c2d[] = "Move Left";
    outtextxy(col1X + 200, 210, c2d);
    
    setcolor(COLOR(255, 255, 255));
    char c3[] = "D";
    outtextxy(col1X + 20, 240, c3);
    setcolor(COLOR(150, 200, 255));
    char c3d[] = "Move Right";
    outtextxy(col1X + 200, 240, c3d);
    
    setcolor(COLOR(255, 255, 255));
    char c4[] = "LEFT CLICK";
    outtextxy(col1X + 20, 270, c4);
    setcolor(COLOR(150, 200, 255));
    char c4d[] = "Shoot";
    outtextxy(col1X + 200, 270, c4d);
    
    setcolor(COLOR(255, 255, 255));
    char c5[] = "RIGHT CLICK";
    outtextxy(col1X + 20, 300, c5);
    setcolor(COLOR(150, 200, 255));
    char c5d[] = "Rocket Jump";
    outtextxy(col1X + 200, 300, c5d);
    
    setcolor(COLOR(255, 255, 255));
    char c6[] = "ESC";
    outtextxy(col1X + 20, 330, c6);
    setcolor(COLOR(150, 200, 255));
    char c6d[] = "Pause/Exit";
    outtextxy(col1X + 200, 330, c6d);
    
    // oBJECTIVES
    setcolor(COLOR(255, 220, 100));
    settextstyle(10, HORIZ_DIR, 3);
    char obj[] = "OBJECTIVES";
    outtextxy(col1X, 390, obj);
    
    setcolor(COLOR(255, 220, 100));
    line(col1X, 420, col1X + 180, 420);
    
    settextstyle(8, HORIZ_DIR, 2);
    
    // objectives
    setcolor(COLOR(255, 220, 100));
    char o1[] = "1. Collect 3 GOLDEN KEYS";
    outtextxy(col1X + 20, 440, o1);
    
    setcolor(COLOR(100, 255, 150));
    char o2[] = "2. Find the EXIT DOOR";
    outtextxy(col1X + 20, 475, o2);
    
    setcolor(COLOR(255, 255, 255));
    char o3[] = "3. Survive! (HP > 0)";
    outtextxy(col1X + 20, 510, o3);
    
    // gAME INFO
    setcolor(COLOR(100, 255, 150));
    settextstyle(10, HORIZ_DIR, 3);
    char info[] = "GAME INFO";
    outtextxy(col2X, 130, info);
    
    setcolor(COLOR(100, 255, 150));
    line(col2X, 160, col2X + 160, 160);
    
    settextstyle(8, HORIZ_DIR, 2);
    
    // player
    setcolor(COLOR(150, 220, 255));
    char pTitle[] = "PLAYER:";
    outtextxy(col2X + 20, 180, pTitle);
    
    setcolor(COLOR(255, 255, 255));
    char p1[] = "HP: 100";
    outtextxy(col2X + 40, 210, p1);
    
    char p2[] = "Damage: 1 HP/bullet";
    outtextxy(col2X + 40, 240, p2);
    
    // enemy
    setcolor(COLOR(255, 255, 255));
    char eTitle[] = "ENEMY:";
    outtextxy(col2X + 20, 275, eTitle);
    
    char e1[] = "HP: 3";
    outtextxy(col2X + 40, 305, e1);
    
    char e2[] = "Damage: -10 HP/hit";
    outtextxy(col2X + 40, 335, e2);
    
    // tIPS
    setcolor(COLOR(150, 220, 255));
    settextstyle(10, HORIZ_DIR, 3);
    char tips[] = "TIPS & TRICKS";
    outtextxy(col2X, 420, tips);
    
    setcolor(COLOR(150, 220, 255));
    line(col2X, 450, col2X + 200, 450);
    
    settextstyle(8, HORIZ_DIR, 2);
    setcolor(COLOR(255, 255, 255));
    
    char t1[] = "- Shoot from distance";
    outtextxy(col2X + 20, 475, t1);
    
    char t2[] = "- Avoid enemy contact!";
    outtextxy(col2X + 20, 510, t2);
    
    char t3[] = "- Explore everywhere";
    outtextxy(col2X + 20, 545, t3);
    
    // lEVELS
    setcolor(COLOR(255, 220, 100));
    settextstyle(10, HORIZ_DIR, 4);
    char levels[] = "5 LEVELS";
    outtextxy(SCREEN_WIDTH/2 - 90, 600, levels);
    
    settextstyle(8, HORIZ_DIR, 2);
    setcolor(COLOR(255, 255, 255));
    char lvl[] = "Easy -> Medium -> Hard -> Very Hard -> Boss";
    outtextxy(SCREEN_WIDTH/2 - 280, 635, lvl);
    
    // bACK BUTTON
    setcolor(COLOR(180, 130, 0));
    settextstyle(10, HORIZ_DIR, 3);
    char back[] = "Press ESC to go back";
    outtextxy(SCREEN_WIDTH/2 - 179, 701, back);
    
    setcolor(COLOR(255, 200, 0));
    outtextxy(SCREEN_WIDTH/2 - 180, 700, back);
}

void Menu::draw() {
    drawBackground();
    drawTitle();
    drawOptions();
}

void Menu::handleInput() {
    char key = lastKey;
    if (key == 72) { // uP
        selectedOption--;
        if (selectedOption < 0) selectedOption = totalOptions - 1;
    }
    else if (key == 80) { // dOWN
        selectedOption++;
        if (selectedOption >= totalOptions) selectedOption = 0;
    }
}

void Menu::setLastKey(char key) {
    lastKey = key;
}

int Menu::getSelectedOption() {
    return selectedOption;
}
