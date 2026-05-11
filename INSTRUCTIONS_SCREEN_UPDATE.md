# Instructions Screen Color Scheme Update

## Summary
Updated the in-game instructions screen (`drawInstructions()` function in `src/graphics/Menu.cpp`) with a new color scheme as requested.

## Changes Made

### Color Scheme
The new design uses ONLY the following colors as requested:
- **White** (RGB 255, 255, 255) - Removed, replaced with black
- **Yellow** (RGB 200, 150, 0) - For titles and highlights
- **Green** (RGB 0, 150, 50) - For success/positive elements
- **Dark Blue** (RGB 0, 100, 200) - For interactive elements and descriptions
- **Black** (RGB 0, 0, 0) - For main text content

### Background Panels
- **Panel Background**: Light blue (RGB 200, 220, 245) - "xanh nhạt"
- **Panel Gradient**: Subtle gradient from RGB(180,200,230) to RGB(200,220,245)
- **Panel Borders**: Dark blue tones (RGB 100,140,200 and RGB 120,160,220)
- **Shadow**: Black shadow for depth effect

### Section Colors

#### 1. CONTROLS Section
- **Header**: Dark Blue (RGB 0, 100, 200)
- **Key Names**: Black (RGB 0, 0, 0)
- **Descriptions**: Dark Blue (RGB 0, 100, 200)

#### 2. OBJECTIVES Section
- **Header**: Yellow (RGB 200, 150, 0)
- **Item 1 (Keys)**: Yellow (RGB 200, 150, 0)
- **Item 2 (Door)**: Green (RGB 0, 150, 50)
- **Item 3 (HP)**: Black (RGB 0, 0, 0)

#### 3. GAME INFO Section
- **Header**: Green (RGB 0, 150, 50)
- **Player Title**: Dark Blue (RGB 0, 100, 200)
- **Player Stats**: Black (RGB 0, 0, 0)
- **Enemy Title**: Black (RGB 0, 0, 0)
- **Enemy Stats**: Black (RGB 0, 0, 0)

#### 4. TIPS & TRICKS Section
- **Header**: Dark Blue (RGB 0, 100, 200)
- **Tips Text**: Black (RGB 0, 0, 0)

#### 5. LEVELS Section
- **Header**: Yellow (RGB 200, 150, 0)
- **Level Description**: Black (RGB 0, 0, 0)

#### 6. BACK BUTTON
- **Shadow**: Darker Yellow (RGB 180, 130, 0)
- **Main Text**: Bright Yellow (RGB 255, 200, 0)

## Files Modified
- `src/graphics/Menu.cpp` - Updated `drawInstructions()` function

## Files Deleted
- `src/graphics/Menu_new.cpp` - Temporary file (content integrated into Menu.cpp)

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
3. Run `game.exe`
4. Select "INSTRUCTIONS" from the main menu to see the new color scheme

## Design Principles Applied
- **Light background panels** for better readability
- **Dark text on light background** for high contrast
- **Limited color palette** (only yellow, green, dark blue, black)
- **No light blue text** - removed all instances
- **Consistent color coding**:
  - Yellow = Important/Highlights
  - Green = Success/Positive
  - Dark Blue = Interactive/Descriptions
  - Black = Main content text

## Previous Issues Resolved
- ❌ Dark panels with light text (too dark, hard to read)
- ❌ Too many colors (confusing)
- ❌ Light blue text on light background (poor contrast)
- ✅ Light panels with dark text (easy to read)
- ✅ Limited color palette (clean and professional)
- ✅ High contrast text (readable)
