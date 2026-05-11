# Enemy AI Update - Diagonal Shooting & Map Collision

## Summary
Updated enemy AI to shoot diagonally toward the player and added map collision detection (gravity + wall collision) similar to the player character.

## Changes Made

### 1. Enemy.h - Updated `updateEnemy()` Function

#### New Parameters:
- `const Player& player` - Reference to player for calculating shooting direction
- `bool (*isSolidTile)(int row, int col)` - Function pointer for tile collision detection

#### New Features:

**A. Map Collision Detection**
- **Gravity**: Enemies now fall with gravity (same as player)
- **Ground Detection**: Enemies detect solid tiles below them and stand on platforms
- **Wall Collision**: Enemies detect walls and reverse direction when hitting them
- **Screen Bounds**: Enemies stay within screen boundaries

**B. Diagonal Shooting**
- Enemies now calculate direction vector from enemy position to player position
- Bullets are fired diagonally toward the player instead of only horizontally
- Enemy facing direction updates based on player position (left/right)
- Uses normalized direction vector: `(dx, dy) = normalize(player_pos - enemy_pos)`
- Bullet velocity: `vx = dx * BULLET_SPEED`, `vy = dy * BULLET_SPEED`

**C. Improved Movement**
- Movement now respects wall collisions
- Enemies reverse direction when hitting walls, screen edges, or movement range limits
- Facing direction updates correctly based on movement direction

### 2. Level Files - Updated `updateEnemy()` Calls

Updated all 5 level files to pass new parameters:

**Level 1** (`src/levels/Level1.h`):
```cpp
updateEnemy(enemies[i], bullets, MAX_BULLETS, player, isSolidTile);
```

**Level 2** (`src/levels/Level2.h`):
```cpp
updateEnemy(enemies[i], bullets, MAX_BULLETS, player, isSolidTileLevel2);
```

**Level 3** (`src/levels/Level3.h`):
```cpp
updateEnemy(enemies[i], bullets, MAX_BULLETS, player, isSolidTileLevel3);
```

**Level 4** (`src/levels/Level4.h`):
```cpp
updateEnemy(enemies[i], bullets, MAX_BULLETS, player, isSolidTileLevel4);
```

**Level 5** (`src/levels/Level5.h`):
```cpp
updateEnemy(enemies[i], bullets, MAX_BULLETS, player, isSolidTileLevel5);
```

## Technical Details

### Collision Detection Algorithm
Same as player collision detection:
1. Apply gravity to vertical velocity
2. Check ground collision (falling down)
3. Check wall collision (moving horizontally)
4. Update position based on collision results

### Shooting Direction Calculation
```cpp
// Calculate direction from enemy to player
float dx = (float)(targetX - originX);
float dy = (float)(targetY - originY);
float len = sqrtf(dx * dx + dy * dy);

// Normalize direction vector
if (len < 1.0f) len = 1.0f;
dx /= len;
dy /= len;

// Apply to bullet velocity
bullets[i].vx = dx * BULLET_SPEED;
bullets[i].vy = dy * BULLET_SPEED;
```

### Movement Logic
- Enemies move horizontally within their `moveRange`
- When hitting obstacles (walls, screen edges, range limits), they reverse direction
- Facing direction updates based on movement direction

## Gameplay Impact

### Increased Difficulty
- Enemies can now hit the player from any angle, not just horizontally
- Players must be more careful about positioning
- Vertical movement (jumping) no longer provides complete safety

### More Realistic AI
- Enemies actively track and aim at the player
- Enemies respect map geometry (don't float or clip through walls)
- Movement feels more natural with gravity and collision

### Strategic Gameplay
- Players can use terrain to block enemy bullets
- Enemies can be trapped or manipulated using map layout
- Vertical positioning matters more for both offense and defense

## Files Modified
- `src/entities/Enemy.h` - Updated `updateEnemy()` function signature and implementation
- `src/levels/Level1.h` - Updated `updateEnemy()` calls
- `src/levels/Level2.h` - Updated `updateEnemy()` calls
- `src/levels/Level3.h` - Updated `updateEnemy()` calls
- `src/levels/Level4.h` - Updated `updateEnemy()` calls
- `src/levels/Level5.h` - Updated `updateEnemy()` calls

## To Compile and Test

1. Close the running game.exe if it's open
2. Run the build command:
   ```bash
   g++ -g src/main.cpp src/graphics/Menu.cpp -o game.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
   ```
   Or simply run:
   ```bash
   build.bat
   ```
3. Run `game.exe` and test enemy behavior in all levels

## Expected Behavior

### Before Update:
- Enemies shoot bullets horizontally only
- Enemies float in air (no gravity)
- Enemies clip through walls
- Easy to avoid bullets by jumping

### After Update:
- Enemies shoot bullets diagonally toward player
- Enemies fall with gravity and stand on platforms
- Enemies collide with walls and reverse direction
- Bullets track player position, harder to avoid

## Notes
- Enemy shooting cooldown remains the same
- Bullet speed remains the same (BULLET_SPEED = 6.0f)
- Enemy HP system unchanged (still 3 HP per enemy)
- Player bullet collision with enemies unchanged
