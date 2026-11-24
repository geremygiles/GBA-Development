#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include "tile_rendering.h"

extern int xTileIndex;
extern int yTileIndex;

void GetPlayerStartPos();
void MovePlayer();

void CheckCollision(int *deltaX, int *deltaY);

#endif