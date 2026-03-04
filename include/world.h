#ifndef WORLD_H
#define WORLD_H

#define WORLD_HEIGHT 100
#define WORLD_WIDTH 100
#define CELL_SIZE 10

typedef enum{SPRING, SUMMER, AUTUMN, WINTER} Season;
typedef enum { FLOOR_GRASS, FLOOR_DIRT, FLOOR_STONE , FLOOR_SAND, FLOOR_WATER ,FLOOR_SNOW} CellType;


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
    float windSpeed;   // in km/h
    float pirecipitation; // in mm

    CellType CellType;
} Cell;

extern Cell World[WORLD_WIDTH][WORLD_HEIGHT];
extern Time myTime;
void InitWorld();
void UpdateTime();
void UpdateSeasons();
void UpdateTemperature();
#endif // WORLD_H