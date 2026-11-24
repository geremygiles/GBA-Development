/*
Contains functions for loading the levels of the game, including loading them into RAM
Geremy Giles 
11/21/2026
*/

#include "level_loading.h"

#include "toolkit.h"
#include "tile_rendering.h"
#include "player_movement.h"
#include <stdint.h>
#include <string.h>

// Current tile X and Y coordinates
int tileX = 0, tileY = 0;

u16 CreateTiles(u32 *data, OBJ_ATTR *buffer, u16 startIndex, OBJ_ATTR *player, int wordIndex) 
{
    u16 tilesProcessed = 0;

    for (int offset = 28; offset >= 0; offset -= 4)
    {
        uint8_t tileData = (*data >> offset) & 0xF; // extract current tile data
        
        if (tileData == PLAYER) 
        {
            // Replace the player's tile with a standard ground tile
            *data = (GROUND << offset) | (*data & ~(0xF << offset)); 

            // Create player then proceed with regular ground tile
            *player = buffer[startIndex + tilesProcessed];

            // Store these indices for player movement
            xTileIndex = offset;
            yTileIndex = wordIndex;

            // Set tile ID and palette ID
            u32 tileID = tileData * 4; // 4 tiles per obj
            u32 paletteID = 0;
            
            // Set Attribute 0: Y-coord, gfx, and shape
            player->attr0 = ATTR0_SQUARE;
            player->attr0 = (player->attr0 & ~YPOS_MASK) | (tileY & YPOS_MASK); 

            // Set Attribute 1: X-coord, size, and flipping
            player->attr1 = ATTR1_SIZE_16; 
            player->attr1 = (player->attr1 & ~XPOS_MASK) | (tileX & XPOS_MASK);

            player->attr2 = (tileID | paletteID); // Set attribute 2: Tile ID, Z Order, and color palette
            
            tilesProcessed++;
            tileData = GROUND;
        }

        if (tileData > EMPTY_TILE && tileData < LINE_DELIM) 
        { // Create the proper tile if 0 < tileData < 15

            // Protect against overflow
            if (startIndex + tilesProcessed >= 128) break;

            OBJ_ATTR *tileObj = &buffer[startIndex + tilesProcessed];

            // Set tile ID and palette ID
            u32 tileID = tileData * 4; // 4 tiles per obj
            u32 paletteID = 0;
            
            // Set Attribute 0: Y-coord, gfx, and shape
            tileObj->attr0 = ATTR0_SQUARE;
            tileObj->attr0 = (tileObj->attr0 & ~YPOS_MASK) | (tileY & YPOS_MASK); 

            // Set Attribute 1: X-coord, size, and flipping
            tileObj->attr1 = ATTR1_SIZE_16; 
            tileObj->attr1 = (tileObj->attr1 & ~XPOS_MASK) | (tileX & XPOS_MASK);

            tileObj->attr2 = (tileID | paletteID); // Set attribute 2: Tile ID, Z Order, and color palette
        
            tilesProcessed++; // count tiles processed
            tileX += TILE_SIZE;
        }
        else if (tileData == LINE_DELIM) 
        { // line delimeter, advance to the next line and reset x
            tileY += TILE_SIZE;
            tileX = 0;
        }
        else
        { // empty tile, move to next tile pos
            tileX += TILE_SIZE;
        }
    }

    return tilesProcessed;
}


unsigned int currentLevel[20] __attribute__((aligned(4))) = {0};

void LoadLevel(const unsigned int *levelToLoad, OBJ_ATTR *buffer, OBJ_ATTR *player) 
{


    memcpy(currentLevel, levelToLoad, sizeof(currentLevel));

    tileX = 0, tileY = 0;

    u16 index = 1; // offset to avoid overwriting files
    for (int ii = 0; ii < 20; ii++) 
    {
        index += CreateTiles(&currentLevel[ii], buffer, index, player, ii);
    }    
}


