/*
The functions needed for loading the levels for my game.
Geremy Giles
11/21/2026
*/

#ifndef LEVEL_LOADING_H
#define LEVEL_LOADING_H

#include "tile_rendering.h"
// Tile types
#define EMPTY_TILE  0
#define BRKEN_GRND  1
#define FRCTR_GRND  2
#define GROUND      3
#define DSTRCT_WALL 4
#define BOMB        5
#define KEY         6
#define WALL        7
#define PLAYER      8
#define DOOR        9
#define LINE_DELIM  15

// Current level
extern unsigned int currentLevel[20];

// Load a level into RAM
void LoadLevel(const unsigned int *levelToLoad, OBJ_ATTR *buffer, OBJ_ATTR *player);

// Create tiles for the specified data
u16 CreateTiles(u32 data, OBJ_ATTR *buffer, u16 startIndex, OBJ_ATTR *player);

#endif