#include "raylib.h"
#include "raygui.h"
#include "world.h"

void DrawWorld(Cell (*worldGrid)[WORLD_HEIGHT]);
void DrawSunFade(float time);
void DrawClouds(Cloud clouds[MAX_CLOUD]);
