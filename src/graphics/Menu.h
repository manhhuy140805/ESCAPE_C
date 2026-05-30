#ifndef MENU_H
#define MENU_H

#include <graphics.h>

class Menu {
private:
    int selectedOption; // 0
    int totalOptions;
    int lastKey; // lưu phím cuối để tránh đọc lại
    
public:
    Menu();
    void draw();
    void handleInput();
    int getSelectedOption();
    void drawTitle();
    void drawOptions();
    void drawInstructions();
    void drawBackground();
    void drawBox(int x1, int y1, int x2, int y2, int color, bool filled);
    void drawButton(int x, int y, int width, int height, char* text, bool selected);
    void setLastKey(char key);
};

#endif
