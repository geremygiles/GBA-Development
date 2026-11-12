/*
A simple project for learning how input is handled on the GBA. The color displayed on the screen will change depending on the key pressed.
Geremy Giles
11/11/2026
*/

#include "toolkit.h"

// Input data
u32 __key_curr, __key_prev = 0;

int main()
{
    // Set the display to Video Mode 3 for simple rendering, with background 2
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2; // The OR bitwise operator combines 0x0003 and 0x0400 into 0x0403

    // Game loop
    while (1) 
    {
        vsync();
        
        readInput();

        if (key_down(KEY_A)) { drawSmile(RED); }
        else if (key_down(KEY_B)) { fillScreen(BLUE); }
        else if (key_down(KEY_START)) { fillScreen(ORANGE); }
    }

    return 0;
}
