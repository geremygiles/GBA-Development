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
    vram_mem[120 + 80*240] = LIGHT_BLUE; // Write the light blue color to the pixel at 120, 80
    vram_mem[120 + 81*240] = LIGHT_BLUE;
    vram_mem[120 + 82*240] = LIGHT_BLUE;
    vram_mem[120 + 83*240] = LIGHT_BLUE;
    vram_mem[120 + 84*240] = LIGHT_BLUE;

    while (1);

    return 0;
}