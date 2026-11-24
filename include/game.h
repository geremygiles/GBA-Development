#ifndef GAME_H

#define GAME_H

#include "tile_rendering.h"

// Double buffer for the OAM
extern OBJ_ATTR obj_buffer[128];

// Player reference
extern OBJ_ATTR *player;

extern int objCount;

extern int levelIndex;

void CopySpriteData();

void LoadNextLevel();

#endif