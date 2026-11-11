/*
The defines and inline functions needed for developing on the GBA.
Geremy Giles
Rev 11/11/2026
*/

// Check if already defined
#ifndef TOOLKIT_H
#define TOOLKIT_H

#include <stdbool.h>

// Typedefs
typedef unsigned int u32;
typedef volatile unsigned int vu32; // needs to be read at each call
typedef unsigned short u16;
typedef volatile unsigned short vu16; // needs to be read at each call

// Define the addresses for the VRAM and IO Registers
#define MEM_VRAM     0x06000000
#define MEM_IO       0x04000000

// Define a pointer to the Video Memory
#define vram_mem ((u16*)MEM_VRAM)

// Define a pointer to the Display settings control (using volatile so the compiler always checks value)
// Using a 32 bit int to optimize for 32-bit processor
// The 0x0000 is redundant, but is present to show which part of the register we are accessing
// 0x0000 is for the LCD controls
#define REG_DISPCNT *((vu32*)(MEM_IO+0x0000))

// Define a pointer to the display status 
// Must use 16-bit short to avoid r/w to REG_VCOUNT
#define REG_DISPSTAT *((vu16*)(MEM_IO+0x0004))

// Define a pointer to the key input register
// Masked to 16-bit with KEY_MASK in readInput
#define REG_KEYINPUT *((vu32*)(MEM_IO+0x0130))

// Define the value for video mode 3
#define DCNT_MODE3 0x0003

// Define the value for background 2
#define DCNT_BG2   0x0400

// Define the hex values for 10 different colors
#define RED     0x001F
#define ORANGE  0x013F
#define YELLOW  0x03BF
#define GREEN   0x03E2
#define LT_BLUE 0x7F6E
#define BLUE    0x7D80
#define INDIGO  0x7C06
#define VIOLET  0x7C14
#define PINK    0x7C1D
#define GRAY    0x6B9C

// Define the width and height of the screen
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

/// VSYNC

// Avoids any tearing by waiting until the GBA is rendering in the VBlank.
inline void vsync() {
    while (~REG_DISPSTAT & 1); // In old VBlank, wait for VDraw
    while (REG_DISPSTAT & 1); // In VDraw, wait for VBlank
}

// INPUT

// Define the key masks for each button
#define KEY_A      0x0001
#define KEY_B      0x0002
#define KEY_SELECT 0x0004
#define KEY_START  0x0008
#define KEY_RIGHT  0x0010
#define KEY_LEFT   0x0020
#define KEY_UP     0x0040
#define KEY_DOWN   0x0080
#define KEY_R      0x0100
#define KEY_L      0x0200

// Define the mask used to get the keys from the 32 bit register
#define KEY_MASK 0x03FF

// Create an enum with all the key indexes
enum eKeyIndex 
{
    KI_A, KI_B, KI_SEL, KI_SRT, 
    KI_RIGHT, KI_LEFT, KI_UP, KI_DOWN,
    KI_R, KI_L, KI_MAX
};

// Declarations of current and previous key states (defined in input-testing.c)
extern unsigned int __key_curr, __key_prev;


// Read input
inline void readInput() 
{
    __key_prev = __key_curr;
    __key_curr = ~REG_KEYINPUT & KEY_MASK;
}

// Check key down for the specified key
inline u32 key_down(u32 keyMask) 
{
    return (__key_curr & ~__key_prev) & keyMask;
}


/// DRAWING FUNCTIONS

// Draw a pixel to the screen
inline void drawPixel(int x, int y, u32 color) {
    vram_mem[x + y*240] = color;
}

// Create a circle algorithm (Bresenhamm's Midpoint Circle Algorithm)
// cx = center x, cy = center y, r = radius, semi = whether to draw a half circle
inline void drawCircle(int cx, int cy, int r, u32 color, bool semi) {
    int x = r;
    int y = 0;
    int error = 1 - r;

    while (x >= y) {
        // Top half of circle
        if (semi == false) {
            drawPixel((cx + y), (cy - x), color); 
            drawPixel((cx + x), (cy - y), color); 
            drawPixel((cx - x), (cy - y), color); 
            drawPixel((cx - y), (cy - x), color); 
        }

        // Bottom half of circle
        drawPixel((cx - y), (cy + x), color); 
        drawPixel((cx - x), (cy + y), color); 
        drawPixel((cx + x), (cy + y), color); 
        drawPixel((cx + y), (cy + x), color); 

        y++;
        if (error < 0) {
            error += 2 * y + 1;
        } else {
            x--;
            error += 2 * (y - x) + 1;
        }
    }

}

// Draws my smiley face to the screen, with the specified color
inline void drawSmile(u32 color)
{
    // Image sizing data
    u32 eyeLength = 25;
    u32 leftEyeXCoord = 95;
    u32 eyeYCoord = 35;
    u32 rightEyeXCoord = 145;

    // Draw the eyes
    for (u32 yPos = eyeYCoord; yPos < eyeYCoord + eyeLength; yPos++)
    {
        drawPixel(leftEyeXCoord, yPos, color);
        drawPixel(rightEyeXCoord, yPos, color);
    }

    // Draw the head (circle)
    int circleCenterX = 120;
    int circleCenterY = 80;
    int circleRadius = 70;

    drawCircle(circleCenterX, circleCenterY, circleRadius, color, false);

    // Draw the smile (semi-circle)
    circleCenterX = 120;
    circleCenterY = 80;
    circleRadius = 40;

    drawCircle(circleCenterX, circleCenterY, circleRadius, color, true);
}

// Fill the screen with the specified color
inline void fillScreen(u32 color) 
{
    u32 i, ii = 0;

    // Iterate over all the scanlines
    for (i = 0; i < SCREEN_HEIGHT; i++) 
    {
        // Iterate over each pixel in the line
        for (ii = 0; ii < SCREEN_WIDTH; ii++)
        {
            drawPixel(ii, i, color);
        }
    }
}

#endif