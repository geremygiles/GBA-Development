#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include "tile_rendering.h"

// Local player reference
extern OBJ_ATTR *player;

extern int playerTileIndex;

extern int xTileIndex;
extern int yTileIndex;

void GetPlayerRef(OBJ_ATTR *playerRef);

void GetPlayerStartPos();
void MovePlayer(OBJ_ATTR *buffer);

void CheckCollision(int *deltaX, int *deltaY, OBJ_ATTR *buffer);

#endif