#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>

#define WORLD_HEIGHT 128
#define WORLD_WIDTH 128
#define CHUNK_SIZE 16
#define RENDER_DISTANCE 8
#define CELL_SIZE 10
#define MAX_CLOUD 15

typedef enum { SPRING, SUMMER, AUTUMN, WINTER } Season;
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

typedef struct worldTime {
  int day;
  int month;
  int year;

  float timeOfDay; // 0.0 to 24.0
  Season currentSeason;
} Time;

typedef struct Cell {
  float temperature;   // in Celsius
  float humidity;      // 0.0 to 1.0
  float precipitation; // in mm

  CellType CellType;
} Cell;

typedef struct Cloud {
  float x, y;
  float width, height;
  float speed;
  float intensity;
  bool active;
} Cloud;

typedef struct World {
  float windSpeed;     // in km/h
  float windDirection; // 0.0 to 360.0
  int seed;
  uint32_t seed_elevation;
  uint32_t seed_temperature;
  uint32_t seed_moisture;
  uint32_t seed_erosion;

} World;

#define MAX_CACHED_CHUNKS 1024

typedef struct ChunkData {
  int chunkX;
  int chunkY;
  bool active;
  uint64_t lastAccessedFrame;
  Cell cells[CHUNK_SIZE][CHUNK_SIZE];
} ChunkData;

extern Camera2D camera;

extern World world;
extern ChunkData chunkCache[MAX_CACHED_CHUNKS];
extern uint64_t currentFrame;

ChunkData* GetOrGenerateChunk(int cx, int cy);
Cell GetCell(int gridX, int gridY);
extern Time myTime;
extern Cloud clouds[MAX_CLOUD];

void InitWorld();
void InitCamera();
void InitClouds();
void UpdateClouds(float windSpeed, float windDirection);
void UpdateTime();
void UpdateSeasons();
void UpdateTemperature();
void UpdateWind();

float NoiseCreate(float nx, float ny);
float FractalNoise(float nx, float ny, int octaves, float scale);
void NoiseSetSeed(int seed);
uint32_t hash(uint32_t x);

#endif // WORLD_H