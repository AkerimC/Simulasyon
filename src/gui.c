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
                case FLOOR_GRASS:         color = (Color){34,  139, 34,  255}; break; // orman yeşili
                case FLOOR_DIRT:          color = (Color){139, 90,  43,  255}; break; // toprak
                case FLOOR_STONE:         color = (Color){120, 120, 120, 255}; break; // taş
                case FLOOR_SAND:          color = (Color){210, 180, 100, 255}; break; // kum
                case FLOOR_WATER:         color = (Color){64,  164, 223, 255}; break; // normal su
                case FLOOR_SNOW:          color = (Color){240, 248, 255, 255}; break; // kar
                case FLOOR_DEEP_WATER:    color = (Color){20,  60,  150, 255}; break; // derin okyanus
                case FLOOR_SHALLOW_WATER: color = (Color){100, 190, 230, 255}; break; // sığ su
                case FLOOR_BEACH:         color = (Color){238, 214, 175, 255}; break; // plaj
                case FLOOR_SWAMP:         color = (Color){80,  100, 50,  255}; break; // bataklık
                case FLOOR_ICE:           color = (Color){180, 220, 240, 255}; break; // buz
                case FLOOR_TUNDRA:        color = (Color){150, 160, 130, 255}; break; // tundra
                case FLOOR_TAIGA:         color = (Color){40,  100, 60,  255}; break; // iğne yapraklı orman
                case FLOOR_DESERT:        color = (Color){200, 150, 60,  255}; break; // çöl
                case FLOOR_SAVANNA:       color = (Color){180, 160, 60,  255}; break; // savan
                case FLOOR_TROPICAL:      color = (Color){20,  120, 40,  255}; break; // tropikal orman
                case FLOOR_LAVA:          color = (Color){200, 50,  10,  255}; break; // lav
                case FLOOR_VOLCANIC:      color = (Color){60,  40,  40,  255}; break; // volkanik taş
                case FLOOR_MOUNTAIN:      color = (Color){90,  80,  75,  255}; break; // dağ
                default:                  color = BLACK;                        break;
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