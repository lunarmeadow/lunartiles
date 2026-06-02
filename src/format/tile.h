/*
 *  Copyright (C) 2026 lunarmeadow (she/her)
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 3
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _TILE_H
#define _TILE_H

#include "stdint.h"

#define TILE_EMPTY 0
#define TILE_FULL 1

typedef struct {
    uint8_t northTex, eastTex, southTex, westTex;
    uint8_t shape;
    uint8_t floorTex, ceilingTex;
    uint8_t lightLevel;
} tile_t;

#endif
