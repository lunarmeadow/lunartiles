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

typedef struct {
    int highlightDivs;
    int width, height; // number of grid cells
    int x, y; // selected x, y
    int spacing;
} grid_state_t;

void DrawTileGrid(grid_state_t* grid);
void InitializeTileGrid(grid_state_t* grid, int w, int h, int spacing, int divs);

#endif
