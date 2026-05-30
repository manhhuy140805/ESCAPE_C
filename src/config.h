#ifndef CONFIG_H
#define CONFIG_H

// cấu hình màn hình
// map 40x28, tile 25px
const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 800;
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

// thông số vật lý / điều khiển cơ bản
const float GAME_GRAVITY        = 0.8f; // trọng lực
const float GAME_MAX_FALL_SPEED = 15.0f; // tốc độ rơi tối đa
const float GAME_MOVE_SPEED     = 5.0f; // tốc độ di chuyển ngang
const float GAME_WALK_SLOW_MULTIPLIER = 0.55f;
const float GAME_RUN_FAST_MULTIPLIER  = 1.55f;
const int   GAME_DOUBLE_TAP_FRAMES    = 18;
const float GAME_FRICTION       = 0.5f; // ma sát khi không bấm phím
const float GAME_JUMP_HEIGHT_BL = 2.5f; // mức nhảy
// vận tốc nhảy để đạt ~2.5 block với gravity ~0.8
const float GAME_JUMP_VELOCITY  = 10.0f; // đơn vị pixel/frame

// hệ số tốc độ TP4
extern float GAME_SPEED_MULTIPLIER;
extern int GAME_SPEED_MODE;

// thông số map/tile
const int TILE_SIZE = 25; // 25x25 pixels
const int MAP_COLS  = 44; // 44 cột
const int MAP_ROWS  = 32; // 32 hàng

// màu sắc
const int GAME_COLOR_BG = 0; // đen
const int GAME_COLOR_PLAYER = 9; // xanh dương sáng
const int GAME_COLOR_ENEMY = 12; // đỏ sáng
const int GAME_COLOR_KEY = 14; // vàng
const int GAME_COLOR_DOOR_CLOSED = 8; // xám
const int GAME_COLOR_DOOR_OPEN = 10; // xanh lá
const int GAME_COLOR_WALL = 7; // trắng
const int GAME_COLOR_BULLET = 15; // trắng sáng
const int GAME_COLOR_UI = 11; // cyan

// keys & door
const int GAME_KEYS_REQUIRED = 3;

// game states
enum GameState {
    MENU,
    PLAYING,
    WIN,
    LOSE
};

#endif
