# Raylib World Simulation

A grid-based 2D world simulation built in C using the Raylib library. It features procedurally generated terrain via simplex noise, smooth day/night cycles, and seasonal temperature changes affecting the environment.

## Features

- **Advanced Procedural World Generation:** Terrain is generated using a full 2D Simplex Noise implementation with layered octave noise (`FractalNoise`). To create highly diverse and realistic worlds, the engine calculates 4 distinct noise maps: **Elevation, Temperature, Moisture, and Erosion**. These are combined to form 19 different complex biomes including Deep Oceans, Swamps, Tundras, Taigas, Deserts, Savannas, Tropical Forests, Volcanic regions, and Mountains.
- **Infinite World & Dynamic Loading:** Uses a camera-centric Chunk Data cache system (LRU) to dynamically generate and load world pieces as you explore, ensuring limitless boundaries without high memory consumption.
- **Interactive Camera Controls:** Left or right click and drag the mouse to pan the camera seamlessly across the infinite world, and use the mouse wheel to zoom in and out.
- **Multi-Seed Logic:** Every run uses a unique master seed derived from the system clock (`time(NULL)`). This master seed is hashed to produce 4 separate, deterministic sub-seeds for the environmental maps, guaranteeing a completely different but coherent world each time.
- **Dynamic Time & Seasons:** Integrated time system simulating flow from hours, to days, months, and 4 distinct seasons (Spring, Summer, Autumn, Winter).
- **Environmental Shifts:**
  - **Day/Night Cycle:** The screen smoothly fades into darkness during nighttime hours (18:00 to 08:00) using realistic fading curves.
  - **Temperature & Wind:** Temperature and wind velocity fluctuate locally and globally based on the current season, affecting the simulation visually.
  - **Dynamic Clouds & Weather:** Procedurally generated clouds drift across the screen propelled by the global wind speed and direction. Clouds dynamically spawn relative to the camera position to ensure they appear anywhere in the infinite map.
  - **Seasonal Visuals:** The terrain's color palette shifts dynamically to reflect the current season (e.g., frost in Winter, orange hues in Summer, yellowing in Autumn).

## Noise API

| Function | Description |
|---|---|
| `NoiseSetSeed(int seed)` | Shuffles permutation table with given seed (Fisher-Yates + LCG). Call before `InitWorld()`. |
| `NoiseCreate(float x, float y)` | Returns a single 2D simplex noise value in `[-1, +1]`. |
| `FractalNoise(float x, float y, int octaves, float scale)` | Layered octave noise, normalised to `[-1, +1]`. Used for terrain generation. |

## Building and Running

This project uses a standard `Makefile` for quick compilation using `gcc`.

### Prerequisites
- GCC Compiler (`build-essential`)
- [Raylib](https://github.com/raysan5/raylib) (v5.0+) and its dependencies (GLFW, OpenGL, etc.)

### Commands
Navigate to the root directory `Simulasyon` and run:

- `make` - Compiles the project inside the `build/` directory without running it.
- `make run` - Compiles the project (if there are changes) and immediately launches the executable.
- `make clean` - Removes the compiled object files and the executable.

## Directory Structure

```text
.
├── src/        # C source files (main, GUI, world logic)
├── include/    # C header files (structs, declarations)
├── build/      # Compiled object files and the final executable
├── assets/     # Images, fonts, or other static assets (if any)
└── Makefile    # Build instructions
```
