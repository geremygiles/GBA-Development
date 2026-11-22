/*
A simple project for learning how sprites are rendered on the GBA. 
Geremy Giles
11/15/2026
*/

#include <string.h>
#include "toolkit.h"

#include "tile_rendering.h"
#include "sprites.h"

#include "levels.h"
#include "level_loading.h"

// Input data
u32 __key_curr, __key_prev = 0;

// Player speed 
const u32 playerMoveSpeed = 1;

// Player size
const u16 playerSize = 16;

// Create the double buffer for the OAM
OBJ_ATTR obj_buffer[128];

int main()
{
    // Set the display to Mode 0 for simple tiles, with background 0
    //REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
    // Enable objects and set the mapping mode to 1D 
    REG_DISPCNT = DCNT_OBJ | DCNT_1D;

    #pragma region Smiley Face

    // // Copy the sprite into the tile memory
    // memcpy(&tile_mem[4][0], smiley16Tiles, smiley16TilesLen);

    // // Copy the palette into the palbank
    // memcpy(obj_pal_mem, smiley16Pal, smiley16PalLen);

    // // Initialize all sprites
    // oam_init(obj_buffer, 128);

    // // Create an OBJ_ATTR for my sprite
    // OBJ_ATTR *myObj = &obj_buffer[0];

    // // Set tile ID and palette ID
    // u32 tileID = 0, paletteID = 0;

    // // Set the starting position for the sprite
    // int playerX = 0, playerY = 0;

    
    // myObj->attr0 = ATTR0_SQUARE; // Set Attribute 0: Y-coord, gfx, and shape
    // myObj->attr1 = ATTR1_SIZE_16; // Set Attribute 1: X-coord, size, and flipping
    // myObj->attr2 = (tileID | paletteID); // Set attribute 2: Tile ID, Z Order, and color palette

    // // Copy everything to OAM, so that all objects are initialized to hide
    // oam_copy(oam_mem, obj_buffer, 128);

    #pragma endregion

    #pragma region Level Loading

    // Copy the sprite data and palettes into VRAM

    // normal ground
    memcpy(&tile_mem[4][3*4], groundTiles, groundTilesLen);
    memcpy(obj_pal_mem, groundPal, groundPalLen);

    // walls
    memcpy(&tile_mem[4][7*4], wallStandardTiles, wallStandardTilesLen);
    //memcpy(obj_pal_mem[7], groundPal, groundPalLen);
    
    // player
    memcpy(&tile_mem[4][8*4], playerTiles, playerTilesLen);

    // door
    memcpy(&tile_mem[4][9*4], doorTiles, doorTilesLen);

    // Initialize all sprites
    oam_init(obj_buffer, 128);

    // temp definition, will be overwritten in LoadLevel
    OBJ_ATTR *player = &obj_buffer[0];
    
    // Load the first level
    LoadLevel(level0, obj_buffer, player);

    // Get updated player x & y coord
    
    int playerY = player->attr0 & YPOS_MASK;
    int playerX = player->attr1 & XPOS_MASK;

    // Copy buffer to OAM
    oam_copy(oam_mem, obj_buffer, 128);

    #pragma endregion

    // Game loop
    while (1) 
    {
        vsync();
        
        readInput();

        if (key_down(KEY_A)) { player->attr0 = ATTR0_HIDE; }

        // Update X position
        if (key_held(KEY_RIGHT)) { playerX += (1 * playerMoveSpeed); }
        else if (key_held(KEY_LEFT)) { playerX -= (1 * playerMoveSpeed); }
        
        // Update Y position
        if (key_held(KEY_UP)) { playerY -= (1 * playerMoveSpeed); }
        else if (key_held(KEY_DOWN)) { playerY += (1 * playerMoveSpeed); }

        // clamp the positions before applying to object
        if (playerX > 240) playerX = -playerSize;
        else if (playerX < -playerSize) playerX = 240;

        if (playerY > 160) playerY = -playerSize;
        else if (playerY < -playerSize) playerY = 160;

        // Update the players Y and X with attr0 and attr1, respectively
        player->attr0 = (player->attr0 & ~YPOS_MASK) | (playerY & YPOS_MASK);
        player->attr1 = (player->attr1 & ~XPOS_MASK) | (playerX & XPOS_MASK);
    
        // Copy to OAM
        oam_copy(oam_mem, obj_buffer, 1);
    }

    return 0;
}
