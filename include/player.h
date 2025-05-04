#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Player {
  Vector2 position;
  float baseSpeed;
  float speed;
  float size;
} Player;

#endif
