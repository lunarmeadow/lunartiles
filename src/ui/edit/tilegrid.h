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

#ifndef _TILEGRID_H
#define _TILEGRID_H

#include "../../format/tile.h"

typedef struct ui_context ui_context_t;
typedef struct edit_context edit_context_t;

typedef struct {
    int highlightDivs;
    int width, height; // number of grid cells
    tile_t* tiles;
    int spacing;
} grid_state_t;

void DrawTileGrid(ui_context_t* ui_ctx, edit_context_t* ctx);
void InitializeTileGrid(edit_context_t* ctx, int w, int h, int spacing, int divs);
void FreeTileGrid(edit_context_t* ctx);

#endif
