#include "../include/world.h"
#include <stdlib.h>
#include <math.h>

static const int PERM_SRC[256] = {
    151,160,137, 91, 90, 15,131, 13,201, 95, 96, 53,194,233,  7,225,
    140, 36,103, 30, 69,142,  8, 99, 37,240, 21, 10, 23,190,  6,148,
    247,120,234, 75,  0, 26,197, 62, 94,252,219,203,117, 35, 11, 32,
     57,177, 33, 88,237,149, 56, 87,174, 20,125,136,171,168, 68,175,
     74,165, 71,134,139, 48, 27,166, 77,146,158,231, 83,111,229,122,
     60,211,133,230,220,105, 92, 41, 55, 46,245, 40,244,102,143, 54,
     65, 25, 63,161,  1,216, 80, 73,209, 76,132,187,208, 89, 18,169,
    200,196,135,130,116,188,159, 86,164,100,109,198,173,186,  3, 64,
     52,217,226,250,124,123,  5,202, 38,147,118,126,255, 82, 85,212,
    207,206, 59,227, 47, 16, 58, 17,182,189, 28, 42,223,183,170,213,
    119,248,152,  2, 44,154,163, 70,221,153,101,155,167, 43,172,  9,
    129, 22, 39,253, 19, 98,108,110, 79,113,224,232,178,185,112,104,
    218,246, 97,228,251, 34,242,193,238,210,144, 12,191,179,162,241,
     81, 51,145,235,249, 14,239,107, 49,192,214, 31,181,199,106,157,
    184, 84,204,176,115,121, 50, 45,127,  4,150,254,138,236,205, 93,
    222,114, 67, 29, 24, 72,243,141,128,195, 78, 66,215, 61,156,180
};

static int perm[512];
static int permMod12[512];
static int permReady = 0;

void NoiseSetSeed(int seed) {

    int tmp[256];
    for (int i = 0; i < 256; i++) tmp[i] = PERM_SRC[i];

    unsigned int rng = (unsigned int)seed;
    for (int i = 255; i > 0; i--) {
        rng = rng * 1664525u + 1013904223u;   /* Knuth LCG */
        int j = (int)(rng >> 16) % (i + 1);
        int t = tmp[i]; tmp[i] = tmp[j]; tmp[j] = t;
    }


    for (int i = 0; i < 512; i++) {
        perm[i]      = tmp[i & 255];
        permMod12[i] = perm[i] % 12;
    }
    permReady = 1;
}


static void ensurePerm(void) {
    if (permReady) return;
    NoiseSetSeed(0); 
}

static const float GRAD2[12][2] = {
    { 1, 1}, {-1, 1}, { 1,-1}, {-1,-1},
    { 1, 0}, {-1, 0}, { 1, 0}, {-1, 0},
    { 0, 1}, { 0,-1}, { 0, 1}, { 0,-1}
};

Cell worldGrid[WORLD_WIDTH][WORLD_HEIGHT];
Time myTime = {1, 1, 2026, 8.0f, WINTER};
Cloud clouds[MAX_CLOUD];

void InitWorld() {
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int y = 0; y < WORLD_HEIGHT; y++) {

            float h = FractalNoise((float)x, (float)y, 3, 40.0f);

            if      (h < -0.30f) worldGrid[x][y].CellType = FLOOR_WATER;
            else if (h < -0.05f) worldGrid[x][y].CellType = FLOOR_DIRT;
            else if (h <  0.45f) worldGrid[x][y].CellType = FLOOR_GRASS;
            else                 worldGrid[x][y].CellType = FLOOR_STONE;

            worldGrid[x][y].temperature  = -7.2f;
            worldGrid[x][y].windSpeed    =  3.0f;
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


float NoiseCreate(float nx, float ny) {
    ensurePerm();


    const float F2 = 0.5f * (sqrtf(3.0f) - 1.0f);   
    const float G2 = (3.0f - sqrtf(3.0f)) / 6.0f;    


    float s  = (nx + ny) * F2;
    int   i  = (int)floorf(nx + s);
    int   j  = (int)floorf(ny + s);


    float t   = (float)(i + j) * G2;
    float X0  = (float)i - t;
    float Y0  = (float)j - t;
    float dx0 = nx - X0;      
    float dy0 = ny - Y0;

    int i1 = (dx0 > dy0) ? 1 : 0;
    int j1 = (dx0 > dy0) ? 0 : 1;

    float dx1 = dx0 - (float)i1 + G2;
    float dy1 = dy0 - (float)j1 + G2;
    float dx2 = dx0 - 1.0f + 2.0f * G2;
    float dy2 = dy0 - 1.0f + 2.0f * G2;

    int ii = i & 255;
    int jj = j & 255;
    int gi0 = permMod12[ii      + perm[jj     ]];
    int gi1 = permMod12[ii + i1 + perm[jj + j1]];
    int gi2 = permMod12[ii +  1 + perm[jj +  1]];

    float n0 = 0.0f, n1 = 0.0f, n2 = 0.0f;

    float t0 = 0.5f - dx0 * dx0 - dy0 * dy0;
    if (t0 >= 0.0f) {
        t0 *= t0;
        n0  = t0 * t0 * (GRAD2[gi0][0] * dx0 + GRAD2[gi0][1] * dy0);
    }

    float t1 = 0.5f - dx1 * dx1 - dy1 * dy1;
    if (t1 >= 0.0f) {
        t1 *= t1;
        n1  = t1 * t1 * (GRAD2[gi1][0] * dx1 + GRAD2[gi1][1] * dy1);
    }

    float t2 = 0.5f - dx2 * dx2 - dy2 * dy2;
    if (t2 >= 0.0f) {
        t2 *= t2;
        n2  = t2 * t2 * (GRAD2[gi2][0] * dx2 + GRAD2[gi2][1] * dy2);
    }

    return 70.0f * (n0 + n1 + n2);
}


float FractalNoise(float nx, float ny, int octaves, float scale) {
    float value      = 0.0f;
    float amplitude  = 1.0f;
    float frequency  = 1.0f;
    float maxValue   = 0.0f;

    for (int o = 0; o < octaves; o++) {
        value    += NoiseCreate(nx * frequency / scale,
                               ny * frequency / scale) * amplitude;
        maxValue += amplitude;
        amplitude *= 0.5f;
        frequency *= 2.0f;
    }
    return value / maxValue; 
}



