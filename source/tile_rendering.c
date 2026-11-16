/* 
Implementation of functions declared in tile_rendering.h
Geremy Giles
Rev 11/15/2026
*/

#include "tile_rendering.h"

// Clears the data in each screen entry, and sets it to hide
void oam_init(OBJ_ATTR *obj, u32 count) 
{
    u32 ii = count;
    u32 *dst = (u32*)obj; // Pointer to the first entry in the buffer

    while (ii--) 
    {
        // Each object is a 64-bit structure, so we need to clear all bits except hide (0x0200)
        *dst++ = ATTR0_HIDE; // set the first word to hide 
        *dst++ = 0; // clear the remaining data in the second word
    }

    // copy to OAM
}

void oam_copy(OBJ_ATTR *dst, const OBJ_ATTR *src, u32 count) 
{
    while (count--) 
    {
        *dst++ = *src++;
    }
}