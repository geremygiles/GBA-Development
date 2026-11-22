
#include "player_movement.h"
#include "toolkit.h"

// Player speed 
const u32 playerMoveSpeed = 1;

// Player position
int playerX = 0; 
int playerY = 0;

// Player tile
int playerTile = 0;

// Tickers to increment tile
int xTicker = 8;
int yTicker = 8;

void GetPlayerStartPos(OBJ_ATTR *player) 
{
    playerY = player->attr0 & YPOS_MASK;
    playerX = player->attr1 & XPOS_MASK;
}

void MovePlayer(OBJ_ATTR *player) 
{
    // Create vector of intended movement
    int deltaX = 0; int deltaY = 0;

    deltaX = tri_bool_horz();
    deltaY = tri_bool_vert();

    playerX += (deltaX * playerMoveSpeed); 
    playerY -= (deltaY * playerMoveSpeed); 

    // clamp the positions before applying to object
    if (playerX > 240) playerX = -TILE_SIZE;
    else if (playerX < -TILE_SIZE) playerX = 240;

    if (playerY > 160) playerY = -TILE_SIZE;
    else if (playerY < -TILE_SIZE) playerY = 160;

    // Update the players Y and X with attr0 and attr1, respectively
    player->attr0 = (player->attr0 & ~YPOS_MASK) | (playerY & YPOS_MASK);
    player->attr1 = (player->attr1 & ~XPOS_MASK) | (playerX & XPOS_MASK);
    
}