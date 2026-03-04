# Raylib World Simulation

A grid-based 2D world simulation built in C using the Raylib library. It features dynamically generated terrain, smooth day/night cycles, and seasonal temperature changes affecting the environment.

## Features

- **Procedural World Generation:** Generates a randomized map of water, dirt, and grass cells upon launch.
- **Dynamic Time & Seasons:** Integrated time system simulating flow from hours, to days, months, and 4 distinct seasons (Spring, Summer, Autumn, Winter). 
- **Environmental Shifts:**
  - **Day/Night Cycle:** The screen smoothly fades into darkness during nighttime hours (18:00 to 08:00) using realistic fading curves.
  - **Temperature:** Temperature fluctuates both locally and globally based on the current season (and a bit of randomization).
  - **Visual Weather:** During Winter, grass and dirt tiles dynamically frost over by blending with white, while water remains untouched.

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
