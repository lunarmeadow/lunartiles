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

#include "tilegrid.h"
#include "raylib.h"
#include "raygui.h"
#include <math.h>

void InitializeTileGrid(grid_state_t* grid, int w, int h, int spacing, int divs)
{
    grid->width = w;
    grid->height = h;
    grid->spacing = spacing;
    grid->highlightDivs = divs * spacing;
}

void DrawTileGrid(grid_state_t* grid)
{
    // derived from lavanda line color
    Color minor = GetColor(0x6374a0ff);
    Color major = GetColor(0x7184b7ff);
    Color median = GetColor(0x67b7b2ff);

    Color cur;

    for(int x = 0; x <= grid->width * grid->spacing; x += grid->spacing)
    {
        // calculate color points
        if(x == round(grid->width / 2.0f) * grid->spacing)
            cur = median;
        else if(x % grid->highlightDivs == 0)
            cur = major;
        else
            cur = minor;

        DrawLine(x, 0, x, grid->height * grid->spacing, cur);
    }

    for(int y = 0; y <= grid->height * grid->spacing; y += grid->spacing)
    {
        if(y == round(grid->height / 2.0f) * grid->spacing)
            cur = median;
        else if(y % grid->highlightDivs == 0)
            cur = major;
        else
            cur = minor;

        DrawLine(0, y, grid->width * grid->spacing, y, cur);
    }
}
