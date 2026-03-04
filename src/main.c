
#include "raylib.h"
#include "../include/world.h"
#include "../include/gui.h"
#include "../include/raygui.h"
#include <stdlib.h>

int main(void)
{

    InitWindow(WORLD_WIDTH * CELL_SIZE, WORLD_HEIGHT * CELL_SIZE, "World Simulation");
    InitWorld();
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        myTime.timeOfDay += GetFrameTime() *1;
        UpdateTime();


        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawWorld(World);
        DrawSunFade(myTime.timeOfDay);

        const char* seasonNames[] = {"SPRING", "SUMMER", "AUTUMN", "WINTER"};
        DrawText(TextFormat("Saat: %.2f Day: %d Month:%d Season:%s Temperature: %.2f", myTime.timeOfDay, myTime.day, myTime.month, seasonNames[myTime.currentSeason], World[0][0].temperature), 10, 10, 20, BLACK );
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}