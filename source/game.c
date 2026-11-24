/*
A simple project for learning how sprites are rendered on the GBA. 
Geremy Giles
11/15/2026
*/

#include "game.h"

#include <string.h>
#include "toolkit.h"

#include "tile_rendering.h"
#include "sprites.h"

#include "levels.h"
#include "level_loading.h"

#include "player_movement.h"


// Input data
u32 __key_curr, __key_prev = 0;

// Create the double buffer for the OAM
OBJ_ATTR obj_buffer[128];

// Current level index
int levelIndex = 0;

int main()
{
    // Set the display to Mode 0 for simple tiles, with background 0
    //REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
    // Enable objects and set the mapping mode to 1D 
    REG_DISPCNT = DCNT_OBJ | DCNT_1D;

    #pragma region Level Loading

    // Copy the sprite data and palettes into VRAM
    CopySpriteData();

    // Initialize all sprites
    oam_init(obj_buffer, 128);

    // temp definition, will be overwritten in LoadLevel
    OBJ_ATTR *player = &obj_buffer[0];
    
    // Load the first level
    LoadLevel(levels[levelIndex], obj_buffer, player);

    GetPlayerRef(player);
    GetPlayerStartPos();

    // Copy buffer to OAM
    oam_copy(oam_mem, obj_buffer, 128);

    #pragma endregion

    // Game loop
    while (1) 
    {
        vsync();
        
        readInput();

        // if (key_down(KEY_A)) { player->attr0 = ATTR0_HIDE; }

        MovePlayer(obj_buffer);

        // Copy to OAM
        oam_copy(oam_mem, obj_buffer, 128);
    }

    return 0;
}

void CopySpriteData()
{
    // normal ground
    memcpy(&tile_mem[4][GROUND * 4], groundTiles, groundTilesLen);
    memcpy(obj_pal_mem, groundPal, groundPalLen);

    // walls
    memcpy(&tile_mem[4][WALL * 4], wallStandardTiles, wallStandardTilesLen);
    // memcpy(obj_pal_mem[7], groundPal, groundPalLen);

    // player
    memcpy(&tile_mem[4][PLAYER * 4], playerTiles, playerTilesLen);

    // door
    memcpy(&tile_mem[4][DOOR * 4], doorTiles, doorTilesLen);
}


