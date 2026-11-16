/*
A simple project for learning how sprites are rendered on the GBA. 
Geremy Giles
11/15/2026
*/

#include <string.h>
#include "toolkit.h"
#include "tile_rendering.h"
#include "smiley_half.h"

// Input data
//u32 __key_curr, __key_prev = 0;

// Create the double buffer for the OAM
OBJ_ATTR obj_buffer[128];

int main()
{
    // Set the display to Mode 0 for simple tiles, with background 0
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0; 

    // Copy the sprite into the tile memory
    memcpy(&tile_mem[4][0], smiley_halfTiles, smiley_halfTilesLen);

    // Copy the palette into the palbank
    memcpy(obj_pal_mem, smiley_halfPal, smiley_halfPalLen);

    // Initialize all sprites
    oam_init(obj_buffer, 128);

    // Create an OBJ_ATTR for my sprite
    OBJ_ATTR *myObj = &obj_buffer[0];

    // Set tile ID and palette ID
    u32 tileID = 0, paletteID = 0;

    // Set Attribute 0: Y-coord, gfx, and shape
    myObj->attr0 |= ATTR0_SQUARE;
    myObj->attr1 |= ATTR1_SIZE_8;
    myObj->attr2 |= (tileID | paletteID);

    oam_copy(oam_mem, myObj, 1);

    // Game loop
    while (1) 
    {
        //vsync();
        
        //readInput();

        //if (key_down(KEY_A)) { drawSmile(RED); }
        //else if (key_down(KEY_B)) { fillScreen(BLUE); }
        //else if (key_down(KEY_START)) { fillScreen(ORANGE); }
    }

    return 0;
}
