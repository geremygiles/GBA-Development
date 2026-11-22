/*
Contains functions for loading the levels of the game, including loading them into RAM
Geremy Giles 
11/21/2026
*/

#include "toolkit.h"
#include "tile_rendering.h"
#include <stdint.h>
#include <string.h>

// Current tile X and Y coordinates
int tileX = 0, tileY = 0;

void CreateTiles(u32 data, OBJ_ATTR *buffer, u16 startIndex) 
{
    u16 offset = 28;
    u16 tilesProcessed = 0;

    while (offset > 0) 
    {
        uint8_t tileData = (data >> offset) & 0xF; // extract current tile data
        
        if (tileData > 0 && tileData < 15) 
        { // Create the proper tile if 0 < tileData < 15
            OBJ_ATTR *tileObj = &buffer[startIndex + tilesProcessed];

            // Set tile ID and palette ID
            u32 tileID = tileData, paletteID = 0;

            tileObj->attr0 = ATTR0_SQUARE; // Set Attribute 0: Y-coord, gfx, and shape
            tileObj->attr1 = ATTR1_SIZE_16; // Set Attribute 1: X-coord, size, and flipping
            tileObj->attr2 = (tileID | paletteID); // Set attribute 2: Tile ID, Z Order, and color palette
        
            tileX += 8; // move to the next 
        }
        else if (tileData == 15) 
        { // line delimeter, advance to the next line and reset x
            tileY += 8;
            tileX = 0;
        }
        else tileX += 8;

        tilesProcessed += 1; // advance to the next tile
        offset -= 4;
        

        

        
        // switch (tileData) 
        // {
        //     case 0: // no tile, increase tile pos & do nothing
        //         tileX += 8;
        //         break;
        //     case 1: // broken tile

        //         break;
        //     case 2: // fractured ground

        //         break;
        //     case 3: // normal ground
        //         OBJ_ATTR *tileObj = &buffer[startIndex + tilesProcessed];

        //         // Set tile ID and palette ID
        //         u32 tileID = 3, paletteID = 0;

        //         tileObj->attr0 = ATTR0_SQUARE; // Set Attribute 0: Y-coord, gfx, and shape
        //         tileObj->attr1 = ATTR1_SIZE_16; // Set Attribute 1: X-coord, size, and flipping
        //         tileObj->attr2 = (tileID | paletteID); // Set attribute 2: Tile ID, Z Order, and color palette
        //         break;
        //     case 4: // destructable wall

        //         break;
        //     case 5: // normal ground w/ tile

        //         break;
        //     case 6: // normal ground w/ key

        //         break;
        //     case 7: // wall

        //         break;
        //     case 8: // normal ground w/ player

        //         break;
        //     case 9: // door

        //         break;
        //     case 15: // line delimiter, start next line

        // }
    }
}


unsigned int currentLevel[20] __attribute__((aligned(4))) = {0};

void LoadLevel(const unsigned int *levelToLoad, OBJ_ATTR *buffer) 
{
    memcpy(currentLevel, levelToLoad, sizeof(currentLevel));

    for (int ii = 0; ii < 20; ii++) 
    {
        CreateTiles(currentLevel[ii], buffer, ii);
    }    
}


