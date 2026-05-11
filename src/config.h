#ifndef CONFIG_H
#define CONFIG_H

// Cấu hình màn hình
// Map 40x28, tile 25px -> 1000x700; cho thêm viền hiển thị
const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 800;
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

// Thông số vật lý / điều khiển cơ bản
const float GAME_GRAVITY        = 0.8f;   // Trọng lực
const float GAME_MAX_FALL_SPEED = 15.0f;  // Tốc độ rơi tối đa
const float GAME_MOVE_SPEED     = 5.0f;   // Tốc độ di chuyển ngang
const float GAME_FRICTION       = 0.5f;  // Ma sát khi không bấm phím (giảm ma sát)
const float GAME_JUMP_HEIGHT_BL = 2.5f;   // Mức nhảy: 2.5 block (tham chiếu)
// Vận tốc nhảy để đạt ~2.5 block với gravity ~0.8
const float GAME_JUMP_VELOCITY  = 10.0f;  // Đơn vị pixel/frame (hướng lên)

// Thông số map/tile (theo mô tả game)
const int TILE_SIZE = 25;      // 25x25 pixels
const int MAP_COLS  = 44;      // 44 cột
const int MAP_ROWS  = 32;      // 32 hàng

// Màu sắc (thêm prefix GAME_ để tránh conflict với Windows)
const int GAME_COLOR_BG = 0;         // Đen
const int GAME_COLOR_PLAYER = 9;     // Xanh dương sáng
const int GAME_COLOR_ENEMY = 12;     // Đỏ sáng
const int GAME_COLOR_KEY = 14;       // Vàng
const int GAME_COLOR_DOOR_CLOSED = 8;  // Xám
const int GAME_COLOR_DOOR_OPEN = 10;   // Xanh lá
const int GAME_COLOR_WALL = 7;       // Trắng
const int GAME_COLOR_BULLET = 15;    // Trắng sáng
const int GAME_COLOR_UI = 11;        // Cyan

// Keys & door
const int GAME_KEYS_REQUIRED = 3;

// Game states
enum GameState {
    MENU,
    PLAYING,
    WIN,
    LOSE
};

#endif
