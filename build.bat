@echo off
chcp 65001>nul
echo Building Parkour 2D Game...

C:\TDM-GCC-32\bin\g++.exe -g ^
    src\main.cpp ^
    src\graphics\Menu.cpp ^
    -o game.exe ^
    -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

if %errorlevel% equ 0 (
    echo Build successful!
    echo Run game.exe to play
) else (
    echo Build failed!
)
pause
