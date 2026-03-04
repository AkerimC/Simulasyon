#include "../include/world.h"
#include <stdlib.h>

Cell World[WORLD_WIDTH][WORLD_HEIGHT];
Time myTime = {1, 1, 2026, 8.0f, WINTER};

void InitWorld() {
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int y = 0; y < WORLD_HEIGHT; y++) {

            int luck = rand() % 100;
            if (luck < 10) World[x][y].CellType = FLOOR_WATER;
            else if (luck < 20) World[x][y].CellType = FLOOR_DIRT;
            else World[x][y].CellType = FLOOR_GRASS;

            World[x][y].temperature = 7.2f;
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
    }

    if(myTime.day > 30) {
        myTime.month++;
        myTime.day = 1;
    }

    if(myTime.month > 12) {
        myTime.year++;
        myTime.month = 1;
    }
    UpdateSeasons();
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
            World[x][y].temperature = baseTemp + luck;
        }
    }
}
