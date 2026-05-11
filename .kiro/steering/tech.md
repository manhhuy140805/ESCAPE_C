# Technology Stack

## Language & Compiler
- **Language**: C/C++
- **Compiler**: MinGW GCC (TDM-GCC-32)
- **Standard**: C++98/C++03 compatible (no modern C++ features)
- **Platform**: Windows 7+

## Graphics Library
- **Primary**: WinBGIM (Windows BGI - Borland Graphics Interface)
- **Header**: `graphics.h`
- **Dependencies**: 
  - `libbgi` - Core graphics library
  - `libgdi32` - Windows GDI
  - `libcomdlg32`, `libuuid`, `liboleaut32`, `libole32` - Windows system libraries

## Additional Libraries
- `conio.h` - Console I/O (keyboard input with `kbhit()`, `getch()`)
- `windows.h` - Windows API (`GetAsyncKeyState()` for real-time input, `Sleep()`)
- `cmath` - Mathematical functions for algorithms

## Build System

### Compilation Command
```bash
g++ -g src/main.cpp src/graphics/Menu.cpp -o game.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
```

### Build Script
- **File**: `build.bat`
- **Usage**: Run `build.bat` to compile the project
- **Output**: `game.exe` in project root

### Compiler Flags
- `-g` - Include debug symbols
- `-lbgi` - Link BGI graphics library
- `-lgdi32` - Link Windows GDI32
- `-lcomdlg32 -luuid -loleaut32 -lole32` - Windows COM/OLE support

## Development Environment
- **Recommended IDEs**: Dev-C++, Code::Blocks
- **Alternative**: Visual Studio Code with MinGW configured
- **Required**: TDM-GCC-32 installed at `C:\TDM-GCC-32\` (or adjust path in build.bat)

## Graphics Configuration
- **Screen Resolution**: 1100x800 pixels
- **Map Dimensions**: 44 columns × 32 rows
- **Tile Size**: 25×25 pixels
- **Frame Rate**: 60 FPS (16ms frame delay)
- **Double Buffering**: Manual page flipping with `setactivepage()` / `setvisualpage()`

## Color System
- Uses BGI color constants (0-15) and custom RGB colors via `COLOR(r,g,b)` macro
- Custom colors defined in code for specific game elements

## Common Commands

### Build
```bash
build.bat
```

### Run
```bash
game.exe
```

### Clean Build
```bash
del game.exe
build.bat
```

## Algorithm Implementations
All primitive drawing operations use custom implementations (not library functions):
- **Bresenham Line Algorithm** - All line drawing
- **Midpoint Circle Algorithm** - Circle drawing
- **Midpoint Ellipse Algorithm** - Ellipse drawing
- **Flood Fill** - Polygon filling (recursive)
- **Fractal Algorithms** - Koch curves, Dragon curves for decorations

## Performance Considerations
- Frame delay: 16ms (60 FPS target)
- Double buffering prevents flickering
- Collision detection uses tile-based grid system
- Object pooling for bullets (fixed arrays, no dynamic allocation)
