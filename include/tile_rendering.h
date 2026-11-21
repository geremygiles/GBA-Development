/*
The defines and inline functions needed for rendering tiles on the GBA.
Geremy Giles
Rev 11/15/2026
*/

// Check if already defined
#ifndef TILE_RENDERING_H
#define TILE_RENDERING_H

#include "toolkit.h"



// Typedefs

// Single tile, 8x8 pixels @ 4bpp: 256 bits, 32 bytes, 8 half-words
typedef struct { u32 data[8]; } TILE, TILE4BPP;

// Charblock, 32x16 tiles, 512 tiles total
typedef TILE CHARBLOCK[512];

// Object Attributes, used for creating an object
typedef struct OBJ_ATTR
{
    u16 attr0;
    u16 attr1;
    u16 attr2;
    s16 fill;
} __attribute__((aligned(4))) OBJ_ATTR;

// Function declarations
void oam_init(OBJ_ATTR *obj, u32 count);
void oam_copy(OBJ_ATTR *dst, const OBJ_ATTR *src, u32 count);

// Memory addresses

// Define the tile memory as a pointer to a charblock 
// (0-5 blocks, 0-3 for backgrounds, 4-5 for sprites)
#define tile_mem  ((CHARBLOCK*)0x06000000)

// Define the palette memory for sprites
#define obj_pal_mem ((void*)0x05000200)

// Define the OAM
#define oam_mem ((OBJ_ATTR*)0x07000000)

// Define the hex values for Mode 0 and Background 0
#define DCNT_MODE0 0x0000
#define DCNT_BG0   0x0100

// Define the hex value for displaying the object layer
#define DCNT_OBJ   0x1000

// Define the hex value for 1D tile mapping
#define DCNT_1D    0x0040

// Attributes

// ATTR0
// GFX
#define ATTR0_HIDE   0x0200
// Color depth mode
#define ATTR0_4BPP   0x0000
// Sprite Shape
#define ATTR0_SQUARE 0x0000

// ATTR1
// Flipping

// Sprite size
#define ATTR1_SIZE_8  0x0000
#define ATTR1_SIZE_16 0x4000

#endif