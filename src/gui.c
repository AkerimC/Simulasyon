
#include "../include/gui.h"
#include "raylib.h"
#include "../include/raygui.h"
#include "../include/world.h"


void DrawWorld(Cell (*World)[WORLD_HEIGHT]) {
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int y = 0; y < WORLD_HEIGHT; y++) {
            Cell cell = World[x][y];
            Color color;

            switch (cell.CellType) {
                case FLOOR_GRASS:
                    color = GREEN;
                    break;
                case FLOOR_DIRT:
                    color = BROWN;
                    break;
                case FLOOR_STONE:
                    color = GRAY;
                    break;
                case FLOOR_SAND:
                    color = YELLOW;
                    break;
                case FLOOR_WATER:
                    color = BLUE;
                    break;
                case FLOOR_SNOW:
                    color = WHITE;
                    break;
                default:
                    color = BLACK; // Default color for unknown types
            }
            if (myTime.currentSeason == WINTER && World[x][y].CellType != FLOOR_WATER) {
                color = ColorLerp(color, RAYWHITE, 0.3f); 
            }

            DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, color);
        }
    }
}

void DrawSunFade(float time) {
    float fadeAmount = 0.0f;
    if (time  > 18.0f && time < 20.0f) fadeAmount = (time - 18.0f) / 2.5f ;
    else if (time < 6.0f || time > 20.0f) fadeAmount = 0.8f; // Gece
    else if (time  < 8.0f) fadeAmount = 0.8f - (time - 6.0f) / 2.5f;

    if (fadeAmount > 0.0f) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, fadeAmount));
    }
}