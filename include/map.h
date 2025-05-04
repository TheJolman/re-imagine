#ifndef MAP_H
#define MAP_H

#include "raylib-tileson.h"
#include "raylib.h"

typedef struct {
  int width;
  int height;
} Screen;

extern Screen screen;
extern Map tileMap;

#endif
