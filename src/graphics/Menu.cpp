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
    // Vẽ background mê cung
    drawLabyrinthBackground();
    
    // Vẽ các ngôi sao trang trí
    drawStars();
}

void Menu::drawTitle() {
    // Vẽ title với outline đẹp
    drawGameTitle(SCREEN_WIDTH/2 - 320, 80);
}

void Menu::drawOptions() {
    int centerX = SCREEN_WIDTH / 2;
    int startY = 300;
    int spacing = 110;
    
    // START GAME button (vàng)
    drawStartButton(centerX, startY, 460, 80, selectedOption == 0);
    
    // INSTRUCTIONS button (trắng xám)
    drawInstructionsButton(centerX, startY + spacing, 460, 80, selectedOption == 1);
    
    // EXIT button (trắng xám)
    drawExitButton(centerX, startY + spacing * 2, 460, 80, selectedOption == 2);
    
    // Hướng dẫn
    settextstyle(8, HORIZ_DIR, 2);
    setcolor(15);
    char hint[] = "UP/DOWN: Select  |  ENTER: Confirm";
    outtextxy(SCREEN_WIDTH/2 - 220, 680, hint);
}

void Menu::drawInstructions() {
    // Dùng chung background mê cung và các ngôi sao
    drawLabyrinthBackground();
    drawStars();
    
    // Title
    settextstyle(10, HORIZ_DIR, 4);
    setcolor(14);
    char title[] = "HOW TO PLAY";
    outtextxy(SCREEN_WIDTH/2 - 180, 60, title);
    
    settextstyle(8, HORIZ_DIR, 2);
    
    // Controls
    setcolor(15);
    char ctrl[] = "CONTROLS:";
    outtextxy(100, 150, ctrl);
    
    char c1[] = "W / SPACE - Jump";
    char c2[] = "A - Move Left";
    char c3[] = "D - Move Right";
    char c4[] = "LEFT MOUSE - Shoot";
    char c5[] = "ESC - Pause/Exit";
    outtextxy(120, 190, c1);
    outtextxy(120, 230, c2);
    outtextxy(120, 270, c3);
    outtextxy(120, 310, c4);
    outtextxy(120, 350, c5);
    
    // Objectives
    char obj[] = "OBJECTIVES:";
    outtextxy(100, 420, obj);
    
    setcolor(14);
    char o1[] = "Collect 3 GOLDEN KEYS";
    outtextxy(120, 460, o1);
    setcolor(10);
    char o2[] = "Open the EXIT DOOR";
    outtextxy(120, 500, o2);
    setcolor(12);
    char o3[] = "Defeat ENEMIES for bonus points";
    outtextxy(120, 540, o3);
    
    // Tips
    setcolor(15);
    char tips[] = "TIPS:";
    outtextxy(100, 610, tips);
    char t1[] = "Enemies deal 10 damage | Enemies have 3 HP";
    outtextxy(120, 650, t1);
    
    // Back
    setcolor(14);
    char back[] = "Press ESC to go back";
    outtextxy(SCREEN_WIDTH/2 - 140, 730, back);
}

void Menu::draw() {
    drawBackground();
    drawTitle();
    drawOptions();
}

void Menu::handleInput() {
    char key = lastKey;
    if (key == 72) {  // UP
        selectedOption--;
        if (selectedOption < 0) selectedOption = totalOptions - 1;
    }
    else if (key == 80) {  // DOWN
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
