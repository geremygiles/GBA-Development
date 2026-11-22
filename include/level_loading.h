/*
The functions needed for loading the levels for my game.
Geremy Giles
11/21/2026
*/

#ifndef LEVEL_LOADING_H
#define LEVEL_LOADING_H

#include "tile_rendering.h"

// Load a level into RAM
void LoadLevel(const unsigned int *levelToLoad, OBJ_ATTR *buffer);

// Create tiles for the specified data
void CreateTiles(u32 data, OBJ_ATTR *buffer, u16 startIndex);

#endif