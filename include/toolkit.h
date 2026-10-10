/*
The defines and inline functions needed for rendering a simple image on the GBA.
Geremy Giles
10/9/2026
*/

// Check if already defined
#ifndef TOOLKIT_H
#define TOOLKIT_H

// Typedefs
typedef unsigned int u32;
typedef unsigned short u16;

// Define the addresses for the VRAM and IO Registers
#define MEM_VRAM 0x06000000
#define MEM_IO   0x04000000

// Define a pointer to the Video Memory
#define vram_mem ((u16*)MEM_VRAM)

// Define a pointer to the Display settings control (using voliatile so the compiler always checks value)
// The 0x0000 is redundant, but is present to show which part of the register we are accessing
// 0x0000 is for the LCD controls
#define REG_DISPCNT *((volatile u32*)(MEM_IO+0x0000))

// Define the value for video mode 3
#define DCNT_MODE3 0x0003

// Define the value for background 2
#define DCNT_BG2   0x0400


// Define the hex for a light blue
#define LIGHT_BLUE 0x7F6E

#endif