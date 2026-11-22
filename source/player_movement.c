
#include "player_movement.h"

#include "toolkit.h"
#include "level_loading.h"

// Player reference 
OBJ_ATTR *player;

// Player speed 
const u32 playerMoveSpeed = 1;

// Player position
int playerX = 0; 
int playerY = 0;

// Player tile position
int xTileIndex = 0;
int yTileIndex = 0;

// Player tile index, set in level_loading
int playerTileIndex = 0;

// Tickers to increment tile
int xTicker = 8;
int yTicker = 8;

void GetPlayerRef(OBJ_ATTR *playerRef) 
{
    // Player object reference
    player = playerRef;
}

void GetPlayerStartPos() 
{
    playerY = player->attr0 & YPOS_MASK;
    playerX = player->attr1 & XPOS_MASK;
}

void MovePlayer(OBJ_ATTR *buffer) 
{
    // Create vector of intended movement
    int deltaX = 0; int deltaY = 0;

    // Calculate deltas with move speed
    deltaX = tri_bool_horz() * playerMoveSpeed;
    deltaY = tri_bool_vert() * playerMoveSpeed;

    // Check the intended movement against the tiles in that area
    CheckCollision(&deltaX, &deltaY, buffer);

    // Apply to postion
    playerX += deltaX; 
    playerY -= deltaY; 

    xTicker += deltaX;
    yTicker -= deltaY; 

    // Check tickers for tile updates
    if (xTicker > 15)
    { // Moving right, decrement offset to update tile pos
        xTicker = 0;
        xTileIndex -= 4;
        if (xTileIndex < 0)
        {
            xTileIndex = 28;
            yTileIndex += 1;
        }
    }
    else if (xTicker < 0)
    { // Moving left, increment offset
        xTicker = 15;
        xTileIndex += 4;
        if (xTileIndex > 28) 
        {
            xTileIndex = 0;
            yTileIndex -= 1;
        }
    }

    if (yTicker > 15)
    { // Moving down, increment word index
        yTicker = 0;
        yTileIndex += 2;
    }
    else if (yTicker < 0)
    { // Moving up, decrement index
        yTicker = 15;
        yTileIndex -= 2;
    }


    // Screen looping
    // clamp the positions before applying to object
    if (playerX > 240) playerX = -TILE_SIZE;
    else if (playerX < -TILE_SIZE) playerX = 240;

    if (playerY > 160) playerY = -TILE_SIZE;
    else if (playerY < -TILE_SIZE) playerY = 160;

    // Update the players Y and X with attr0 and attr1, respectively
    player->attr0 = (player->attr0 & ~YPOS_MASK) | (playerY & YPOS_MASK);
    player->attr1 = (player->attr1 & ~XPOS_MASK) | (playerX & XPOS_MASK);
    
}

void CheckCollision(int *deltaX, int *deltaY, OBJ_ATTR *buffer) 
{
    int desiredPlayerTile = 0;
    //int horzTileChange = 0;
    //int vertTileChange = 0;

    // Delta X
    // Evaluate desired change
    if ((xTicker + *deltaX + 7) > 15) 
    { // move to tile right
        //horzTileChange = -4;
        desiredPlayerTile = (currentLevel[yTileIndex] >> (xTileIndex - 4)) & 0xF;
    }
    else if ((xTicker + *deltaX - 8) < 0)
    { // move to tile left
        //horzTileChange = 4;
        desiredPlayerTile = (currentLevel[yTileIndex] >> (xTileIndex + 4)) & 0xF;
    }
    else 
    { // stay in current tile
        desiredPlayerTile = (currentLevel[yTileIndex] >> xTileIndex) & 0xF;
    }

    // Does that tile contain a wall?
    if (desiredPlayerTile == WALL || desiredPlayerTile == DSTRCT_WALL)
    { // Yes, change delta to 0
        *deltaX = 0;
    }
    
    // Delta Y, same
    if ((yTicker + *deltaY + 7) > 15)
    { // move to tile down
        //vertTileChange = 2;
        desiredPlayerTile = (currentLevel[yTileIndex + 2] >> xTileIndex) & 0xF;
    }
    else if ((yTicker + *deltaY - 8) < 0)
    { // move to tile up
        //vertTileChange = -2;
        desiredPlayerTile = (currentLevel[yTileIndex - 2] >> xTileIndex) & 0xF;
    }
    else
    { // stay in current tile
        desiredPlayerTile = (currentLevel[yTileIndex] >> xTileIndex) & 0xF;
    }

    // Does that tile contain a wall?
    if (desiredPlayerTile == WALL || desiredPlayerTile == DSTRCT_WALL)
    { // Yes, change delta to 0
        *deltaY = 0;
    }

    if (desiredPlayerTile == GROUND)
    {
        *deltaX = 2;
    }
}