#include "../include/world.h"
#include <stdlib.h>
#include <math.h>

Cell worldGrid[WORLD_WIDTH][WORLD_HEIGHT];
Time myTime = {1, 1, 2026, 8.0f, WINTER};
Cloud clouds[MAX_CLOUD];

void InitWorld() {
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int y = 0; y < WORLD_HEIGHT; y++) {

            int luck = rand() % 100;
            if (luck < 10) worldGrid[x][y].CellType = FLOOR_WATER;
            else if (luck < 20) worldGrid[x][y].CellType = FLOOR_DIRT;
            else worldGrid[x][y].CellType = FLOOR_GRASS;

            worldGrid[x][y].temperature = -7.2f;
            worldGrid[x][y].windSpeed = 3.0f;
            worldGrid[x][y].windDirection = 0.0f;
        }
    }
}

void InitClouds(){
    for(int i=0; i<MAX_CLOUD; i++){
        clouds[i].active = false;
    }
}

void UpdateClouds(float windSpeed, float windDirection){
    for(int i=0; i<MAX_CLOUD; i++){
        if(!clouds[i].active){
            if(rand()%200 == 0){
                clouds[i].active = true;
                int luck = rand() % 4;
                if(luck == 0) {
                    clouds[i].x = -100;
                    clouds[i].y = rand() % (WORLD_HEIGHT * CELL_SIZE);
                } else if(luck == 1){
                    clouds[i].x = WORLD_WIDTH * CELL_SIZE + 100;
                    clouds[i].y = rand() % (WORLD_HEIGHT * CELL_SIZE);
                } else if(luck == 2){
                    clouds[i].y = -100;
                    clouds[i].x = rand() % (WORLD_WIDTH * CELL_SIZE);
                } else {
                    clouds[i].y = WORLD_HEIGHT * CELL_SIZE + 100;
                    clouds[i].x = rand() % (WORLD_WIDTH * CELL_SIZE);
                }
                clouds[i].width = 100 + (rand() % 200);
                clouds[i].height = 50+ (rand() % 100);
                clouds[i].speed = windSpeed;
                clouds[i].intensity = rand() % 100 + 1;
            }
        }
        else{
            float radWind = windDirection * 3.14159f / 180.0f;
            clouds[i].x += cos(radWind) * clouds[i].speed;
            clouds[i].y += sin(radWind) * clouds[i].speed;

            if (clouds[i].x > WORLD_WIDTH * CELL_SIZE + 100 || clouds[i].x < -100 || clouds[i].y > WORLD_HEIGHT * CELL_SIZE + 100 || clouds[i].y < -100){
                clouds[i].active = false;
            }
        }
    }
}

void UpdateSeasons(){
    if (myTime.month == 12 || myTime.month == 1 || myTime.month == 2) {
        myTime.currentSeason = WINTER;
    } else if (myTime.month >= 3 && myTime.month <= 5) {
        myTime.currentSeason = SPRING;
    } else if (myTime.month >= 6 && myTime.month <= 8) {
        myTime.currentSeason = SUMMER;
    } else {
        myTime.currentSeason = AUTUMN;
    }
}

void UpdateTime() {
    if (myTime.timeOfDay >= 24.0f) {
        myTime.timeOfDay -= 24.0f;
        myTime.day++;
        UpdateTemperature();
        UpdateWind();
    }

    if(myTime.day > 30) {
        myTime.month++;
        myTime.day = 1;
        UpdateSeasons();
    }

    if(myTime.month > 12) {
        myTime.year++;
        myTime.month = 1;
    }
    
}

void UpdateTemperature(){
    float baseTemp = 0.0f;
    //kışın 5,6 ilk 14,9 yaz 26,4 son 17,2 ay içinde +-10 derece 
    // gün içinde +-5 derece 
    // gün içinde sıcaklık değişmesi yapılmadı
    if(myTime.currentSeason == WINTER) baseTemp = 5.6f;
    else if(myTime.currentSeason == SPRING) baseTemp = 14.9f;
    else if(myTime.currentSeason == SUMMER) baseTemp = 26.4f;
    else if(myTime.currentSeason == AUTUMN) baseTemp = 17.2f;

    for(int x=0; x<WORLD_WIDTH; x++){
        for(int y=0; y<WORLD_HEIGHT; y++){
            float luck = (rand() % 15) - 7.5f;
            worldGrid[x][y].temperature = baseTemp + luck;
        }
    }
}

void UpdateWind(){
    for(int x=0; x<WORLD_WIDTH; x++){
        for(int y=0; y<WORLD_HEIGHT; y++){
            float luck = (rand() % 3);
            float direction = (rand() % 360);
            worldGrid[x][y].windSpeed = luck + 0.5f;
            worldGrid[x][y].windDirection = direction;
        }
    }
}