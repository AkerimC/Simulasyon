#ifndef WORLD_H
#define WORLD_H

#include <stdbool.h>
#include <stdint.h>

#define WORLD_HEIGHT 150
#define WORLD_WIDTH 150
#define CELL_SIZE 10
#define MAX_CLOUD 15

typedef enum{SPRING, SUMMER, AUTUMN, WINTER} Season;
typedef enum {
    FLOOR_GRASS,
    FLOOR_DIRT,
    FLOOR_STONE,
    FLOOR_SAND,
    FLOOR_WATER,
    FLOOR_SNOW,
    FLOOR_DEEP_WATER,
    FLOOR_SHALLOW_WATER,
    FLOOR_BEACH,
    FLOOR_SWAMP,
    FLOOR_ICE,
    FLOOR_TUNDRA,
    FLOOR_TAIGA,
    FLOOR_DESERT,
    FLOOR_SAVANNA,
    FLOOR_TROPICAL,
    FLOOR_LAVA,
    FLOOR_VOLCANIC,
    FLOOR_MOUNTAIN,
} CellType;


typedef struct worldTime
{
    int day;
    int month;
    int year;

    float timeOfDay; // 0.0 to 24.0
    Season currentSeason;
} Time;

typedef struct {
    float temperature; // in Celsius
    float humidity;    // 0.0 to 1.0
    float precipitation; // in mm

    CellType CellType;
} Cell;

typedef struct {
    float x,y;
    float width, height;
    float speed;
    float intensity;
    bool active;
} Cloud;

typedef struct {
    float windSpeed;   // in km/h
    float windDirection; // 0.0 to 360.0
    int seed;
    uint32_t seed_elevation;
    uint32_t seed_temperature;
    uint32_t seed_moisture;
    uint32_t seed_erosion;

} World;

extern World world;
extern Cell worldGrid[WORLD_WIDTH][WORLD_HEIGHT];
extern Time myTime;
extern Cloud clouds[MAX_CLOUD];

void InitWorld();
void InitClouds();
void UpdateClouds(float windSpeed, float windDirection);
void UpdateTime();
void UpdateSeasons();
void UpdateTemperature();
void UpdateWind();

float NoiseCreate(float nx, float ny);
float FractalNoise(float nx, float ny, int octaves, float scale);
void  NoiseSetSeed(int seed);
uint32_t hash(uint32_t x);

#endif // WORLD_H