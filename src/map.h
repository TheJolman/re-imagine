#ifndef MAP_H
#define MAP_H

#include "raylib.h"

typedef struct {
  Rectangle bounds;
  Color color;
  float borderThickness;
} MyMap;

typedef struct {
  Rectangle bounds;
  Color color;
} Obstacle;

#endif
