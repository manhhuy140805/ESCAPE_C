# Project Structure

## Directory Organization

```
project-root/
├── src/                    # Source code
│   ├── main.cpp           # Entry point, game loop, menu integration
│   ├── config.h           # Global constants and configuration
│   │
│   ├── core/              # Core game systems
│   │   ├── algorithms.h   # Custom drawing algorithms (Bresenham, Midpoint)
│   │   ├── blocks.h       # Tile/block rendering
│   │   ├── buttonStart.h  # UI button components
│   │   ├── decorations.h  # Background decorations, fractal elements
│   │   ├── doublebuffer.h # Double buffering implementation
│   │   └── primitives.h   # Basic shape drawing primitives
│   │
│   ├── entities/          # Game entities
│   │   ├── Player.h       # Player struct, movement, rendering
│   │   ├── Enemy.h        # Enemy AI, patrol, shooting
│   │   └── Items.h        # Keys, doors, collectibles
│   │
│   ├── graphics/          # Graphics and UI
│   │   ├── Menu.h         # Menu header
│   │   ├── Menu.cpp       # Menu implementation
│   │   └── CustomDrawing.h # Custom drawing utilities
│   │
│   ├── levels/            # Level gameplay logic
│   │   ├── Level1.h       # Level 1 gameplay loop
│   │   ├── Level2.h       # Level 2 gameplay loop
│   │   ├── Level3.h       # Level 3 gameplay loop
│   │   ├── Level4.h       # Level 4 gameplay loop
│   │   ├── Level5.h       # Level 5 gameplay loop
│   │   └── LevelCommon.h  # Shared level utilities (HUD, end screens)
│   │
│   ├── map/               # Level map data
│   │   ├── Level1.h       # Level 1 tile map array
│   │   ├── Level2.h       # Level 2 tile map array
│   │   ├── Level3.h       # Level 3 tile map array
│   │   ├── Level4.h       # Level 4 tile map array
│   │   └── Level5.h       # Level 5 tile map array
│   │
│   ├── utils/             # Utility systems
│   │   └── ShootingSystem.h # Bullet management, shooting mechanics
│   │
│   └── demo_algorithms.cpp # Algorithm demonstration/testing
│
├── docs/                  # Documentation
│   ├── MO_TA_GAME.md     # Complete game design document (Vietnamese)
│   ├── THUAT_TOAN.md     # Algorithm documentation
│   └── YEU_CAU.txt       # Academic requirements (TP2, TP3, TP4)
│
├── assets/                # Game assets (currently empty)
├── build.bat             # Build script
└── game.exe              # Compiled executable
```

## Code Organization Patterns

### Header-Only Architecture
- All game code uses header-only files (`.h`)
- Only `Menu.cpp` has separate implementation
- Enables easy inclusion and inline functions
- Uses `static` functions to avoid multiple definition errors

### Entity Pattern
Each entity (Player, Enemy, Item) follows this structure:
```cpp
struct EntityName {
    // Position and dimensions
    int x, y, width, height;
    // State variables
    bool active;
    // Physics/movement
    float vx, vy;
};

static EntityName makeEntity(...) { /* constructor */ }
static void drawEntity(const EntityName& e) { /* rendering */ }
static void updateEntity(EntityName& e) { /* logic */ }
```

### Level Structure
Each level consists of:
- **Map file** (`map/LevelX.h`): 2D tile array defining terrain
- **Gameplay file** (`levels/LevelX.h`): Game loop, collision, win/lose conditions
- **Init function**: `initLevelX()` - Sets up player, enemies, items
- **Run function**: `runGameLevelX()` - Main game loop for that level

### Tile-Based Collision
Maps use integer tile codes:
- `0` = Empty/air
- `1` = Solid block (dirt)
- `2` = Grass block (spawn points for keys/doors)
- `3` = Spike hazard
- `4` = Lava hazard

Collision detection checks tile type at player's bounding box corners.

## Key Files

### Entry Point
- **`src/main.cpp`**: Initializes graphics, runs menu loop, transitions between levels

### Configuration
- **`src/config.h`**: All game constants (screen size, physics, colors, tile size)

### Core Systems
- **`src/core/doublebuffer.h`**: `beginFrame()` / `endFrame()` for flicker-free rendering
- **`src/core/algorithms.h`**: Custom Bresenham/Midpoint implementations (TP2 requirement)
- **`src/utils/ShootingSystem.h`**: Unified bullet system for player and enemies

### Game State
- **`src/entities/Player.h`**: Player physics, HP system, invincibility frames
- **`src/entities/Enemy.h`**: AI patrol, edge detection, shooting behavior
- **`src/levels/LevelCommon.h`**: Shared HUD, end screens, level transitions

## Naming Conventions

### Files
- Header files: `PascalCase.h` (e.g., `Player.h`, `Level1.h`)
- Implementation: `PascalCase.cpp` (only `Menu.cpp`)
- Config/utility: `lowercase.h` (e.g., `config.h`, `algorithms.h`)

### Variables
- Local variables: `camelCase` (e.g., `playerX`, `isJumping`)
- Constants: `UPPER_SNAKE_CASE` with `GAME_` prefix (e.g., `GAME_GRAVITY`, `TILE_SIZE`)
- Struct members: `camelCase` (e.g., `player.vx`, `enemy.active`)

### Functions
- Static functions: `camelCase` (e.g., `drawPlayer()`, `updateEnemy()`)
- Factory functions: `makeEntityName()` (e.g., `makeDefaultPlayer()`, `makeEnemy()`)

### Structs
- `PascalCase` (e.g., `Player`, `Enemy`, `KeyItem`, `DoorItem`)

## Include Patterns

### Standard Order
```cpp
#include <graphics.h>      // Graphics library (always first)
#include <conio.h>         // Console I/O
#include <windows.h>       // Windows API
#include "../config.h"     // Project config
#include "OtherHeaders.h"  // Other project headers
```

### Include Guards
All headers use:
```cpp
#ifndef HEADER_NAME_H
#define HEADER_NAME_H
// ... content ...
#endif
```

## Build Dependencies

### Compilation Units
Only two `.cpp` files are compiled:
1. `src/main.cpp` - Includes all necessary headers
2. `src/graphics/Menu.cpp` - Menu implementation

All other code is header-only and included transitively.

## Extension Guidelines

### Adding a New Level
1. Create `src/map/LevelX.h` with tile array
2. Create `src/levels/LevelX.h` with `initLevelX()` and `runGameLevelX()`
3. Add level transition in previous level's end screen handler
4. Update level count in menu if needed

### Adding a New Entity Type
1. Define struct in appropriate `src/entities/` header
2. Implement `makeEntity()`, `drawEntity()`, `updateEntity()` functions
3. Add collision detection logic in level files
4. Initialize in level's `initLevelX()` function

### Adding Custom Algorithms
1. Implement in `src/core/algorithms.h` as static functions
2. Add comments explaining algorithm steps (academic requirement)
3. Use in rendering code instead of library functions
4. Document in `docs/THUAT_TOAN.md`
