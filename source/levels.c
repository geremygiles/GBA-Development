/*
The levels for the game, converted to hexidecimal words.
Geremy Giles
Rev 11/21/2026
*/

#include "levels.h"

const LEVEL level0[20] __attribute__((aligned(4))) =
{
    0xF0000000,0x00000000,
    0xF0000000,0x00000000,
    0xF0000000,0x00000000,
    0xF0077777,0x77777700,
    0xF0078333,0x33339700,
    0xF0077777,0x77777700,
    0xF0000000,0x00000000,
    0xF0000000,0x00000000,
    0xF0000000,0x00000000,
    0xF0000000,0x00000000,
};

const LEVEL level1[20] __attribute__((aligned(4))) =
{
    0xF0000000,0x00000000,
    0xF0000000,0x00000000,
    0xF0077777,0x77777700,
    0xF0078733,0x33333700,
    0xF0073733,0x37333700,
    0xF0073333,0x37339700,
    0xF0077777,0x77777700,
    0xF0000000,0x00000000,
    0xF0000000,0x00000000,
    0xF0000000,0x00000000,
};

const int levelCount = 2;
const LEVEL * levels[2] =  { level0, level1 };