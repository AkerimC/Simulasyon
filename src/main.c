
#include "raylib.h"
#include "../include/world.h"
#include "../include/gui.h"
#include "../include/raygui.h"
#include <stdlib.h>

int main(void)
{

    InitWindow(WORLD_WIDTH * CELL_SIZE, WORLD_HEIGHT * CELL_SIZE, "World Simulation");
    InitWorld();
    InitClouds();
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        myTime.timeOfDay += GetFrameTime() * 1;
        //myTime.day += 1;
        UpdateTime();

        UpdateClouds(worldGrid[0][0].windSpeed, worldGrid[0][0].windDirection);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawWorld(worldGrid);
        DrawClouds(clouds);
        DrawSunFade(myTime.timeOfDay);

        const char* seasonNames[] = {"SPRING", "SUMMER", "AUTUMN", "WINTER"};
        DrawText(TextFormat("Saat: %.2f Day: %d Month:%d Season:%s Temperature: %.2f Wind Speed: %.2f Wind Direction: %.2f" , myTime.timeOfDay, myTime.day, myTime.month, seasonNames[myTime.currentSeason], worldGrid[0][0].temperature, worldGrid[0][0].windSpeed, worldGrid[0][0].windDirection), 10, 10, 20, BLACK );
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}