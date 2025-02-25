#ifndef MAP_H
#define MAP_H

#include "raylib.h"

typedef struct Map {
  Rectangle bounds;
  Color color;
  float borderThickness;
} Map;

typedef struct Obstacle {
  Rectangle bounds;
  Color color;
} Obstacle;

#endif
