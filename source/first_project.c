/*
First project for the GBA, practicing creating a simple image on the GBA.
Geremy Giles
10/9/2026
*/

#include "toolkit.h"

int main()
{
    // Set the display to Video Mode 3 for simple rendering, with background 2
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2; // The OR bitwise operator combines 0x0003 and 0x0400 into 0x0403

    // Show the image
    

    for (u32 yIndex = 160; yIndex >= 0; yIndex--) {
        for (u32 xIndex = 240; xIndex >= 0; xIndex--) {
            vram_mem[xIndex + yIndex*240] = LIGHT_BLUE; // Write the light blue color to the pixel at 120, 80
        }
    }

    while (1);

    return 0;
}