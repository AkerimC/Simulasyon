#include <stdlib.h>
#include "../include/gui.h"
#include "raylib.h"
#include "../include/raygui.h"
#include "../include/world.h"


void DrawWorld(Cell (*worldGrid)[WORLD_HEIGHT]) {
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int y = 0; y < WORLD_HEIGHT; y++) {
            Cell cell = worldGrid[x][y];
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
            if (myTime.currentSeason == WINTER && worldGrid[x][y].CellType != FLOOR_WATER) {
                color = ColorLerp(color, RAYWHITE, 0.3f); 
            }
            else if (myTime.currentSeason == SUMMER && worldGrid[x][y].CellType != FLOOR_WATER) {
                color = ColorLerp(color, ORANGE, 0.3f); 
            }
            else if (myTime.currentSeason == AUTUMN && worldGrid[x][y].CellType != FLOOR_WATER) {
                color = ColorLerp(color, YELLOW, 0.3f); 
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

void DrawClouds(Cloud clouds[MAX_CLOUD]){
    for(int i=0; i<MAX_CLOUD; i++){
        if(clouds[i].active){
            DrawEllipse(clouds[i].x, clouds[i].y, clouds[i].width, clouds[i].height, Fade(LIGHTGRAY, clouds[i].intensity / 100.0f));
        
            if(clouds[i].intensity > 50 ){
                if(worldGrid[0][0].temperature > 0){
                    for(int j=0; j<10 ; j++){
                        int rx = clouds[i].x + (rand() % (int)clouds[i].width) - clouds[i].width/2;
                        int ry = clouds[i].y + (rand() % (int)clouds[i].height) - clouds[i].height/2;
                        DrawLine(rx ,ry ,rx-4 ,ry-9, Fade(BLUE,0.7f));
                    }
                }
                else{
                    for(int j=0; j<10 ; j++){
                        int rx = clouds[i].x + (rand() % (int)clouds[i].width) - clouds[i].width/2;
                        int ry = clouds[i].y + (rand() % (int)clouds[i].height) - clouds[i].height/2;
                        DrawLine(rx ,ry ,rx-3 ,ry-5, Fade(WHITE,0.7f));
                        DrawLine(rx+2 ,ry+2 ,rx-5 ,ry-3, Fade(WHITE,0.7f));
                    }
                }

            }
        }
    }
}