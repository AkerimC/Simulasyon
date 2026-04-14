
#include "raylib.h"
#include "../include/world.h"
#include "../include/gui.h"
#include "../include/raygui.h"
#include <stdlib.h>
#include <time.h>

int main(void)
{

    InitWindow(WORLD_WIDTH * CELL_SIZE, WORLD_HEIGHT * CELL_SIZE, "World Simulation");

    InitWorld();
    InitClouds();
    InitCamera(); // Ensure camera is initialized before loop
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        currentFrame++;
        
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            Vector2 delta = GetMouseDelta();
            camera.target.x -= delta.x / camera.zoom;
            camera.target.y -= delta.y / camera.zoom;
        }

        float wheel = GetMouseWheelMove();
        if (wheel != 0) {
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            camera.offset = GetMousePosition();
            camera.target = mouseWorldPos;

            camera.zoom += wheel * 0.1f;
            if (camera.zoom < 0.1f) camera.zoom = 0.1f;
            if (camera.zoom > 5.0f) camera.zoom = 5.0f;
        }

        myTime.timeOfDay += GetFrameTime() * 1;
        //myTime.day += 1;
        UpdateTime();

        UpdateClouds(world.windSpeed, world.windDirection);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        DrawWorld();
        DrawClouds(clouds);
        EndMode2D();
        
        DrawSunFade(myTime.timeOfDay);

        Cell center = GetCell((int)(camera.target.x / CELL_SIZE), (int)(camera.target.y / CELL_SIZE));

        const char* seasonNames[] = {"SPRING", "SUMMER", "AUTUMN", "WINTER"};
        DrawText(TextFormat("Saat: %.2f Day: %d Month:%d Season:%s Temperature: %.2f Wind Speed: %.2f Wind Direction: %.2f" , myTime.timeOfDay, myTime.day, myTime.month, seasonNames[myTime.currentSeason], center.temperature, world.windSpeed, world.windDirection), 10, 10, 20, BLACK );
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}