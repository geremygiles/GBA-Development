/*
First project for the GBA, practicing creating a simple image on the GBA.
Geremy Giles
10/9/2026
*/

#include "toolkit.h"
#include <math.h>

int main()
{
    // Set the display to Video Mode 3 for simple rendering, with background 2
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2; // The OR bitwise operator combines 0cx003 and 0cx400 into 0cx403

    // Image data
    u32 eyeLength = 25;
    u32 leftEyeXCoord = 95;
    u32 eyeYCoord = 35;
    u32 rightEyeXCoord = 145;
    
    // Draw the eyes
    for (u32 yPos = eyeYCoord; yPos < eyeYCoord + eyeLength; yPos++) {
        drawPixel(leftEyeXCoord, yPos, LIGHT_BLUE);
        drawPixel(rightEyeXCoord, yPos, LIGHT_BLUE);
    } 


    // Draw the head (circle)
    int circleCenterX = 120;
    int circleCenterY = 80;
    int circleRadius = 70;

    drawCircle(circleCenterX, circleCenterY, circleRadius, false);

    // Draw the smile (semi-circle)
    circleCenterX = 120;
    circleCenterY = 100;
    circleRadius = 30;

    drawCircle(circleCenterX, circleCenterY, circleRadius, true);


    while (1);

    return 0;
}