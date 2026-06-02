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

#include "../context.h"
#include "raylib.h"
#include "raygui.h"
#include <math.h>
#include <stdlib.h>

void InitializeTileGrid(edit_context_t* ctx, int w, int h, int spacing, int divs)
{
    ctx->grid.width = w;
    ctx->grid.height = h;
    ctx->grid.spacing = spacing;
    ctx->grid.highlightDivs = divs * spacing;
    ctx->grid.tiles = nullptr;

    ctx->grid.tiles = calloc(w * h, sizeof(tile_t));
}

void FreeTileGrid(edit_context_t* ctx)
{
    if(ctx->grid.tiles != nullptr)
    {
        free(ctx->grid.tiles);
        ctx->grid.tiles = nullptr;
    }
}

void DrawTileGrid(edit_context_t* ctx)
{
    // derived from lavanda line color
    Color minor = GetColor(0x6374a0ff);
    Color major = GetColor(0x7184b7ff);
    Color median = GetColor(0x67b7b2ff);
    Color tileColor = GetColor(0xff0000ff);
    Color cursorColor = GetColor(0x00ff00ff);

    // draw tilemap
    for(int x = 0; x < ctx->grid.width; x++)
    {
        for(int y = 0; y < ctx->grid.height; y++)
        {
            if(ctx->grid.tiles[x + (ctx->grid.width * y)].shape != 0)
            {
                DrawRectangle(x * ctx->grid.spacing, y * ctx->grid.spacing,
                              ctx->grid.spacing, ctx->grid.spacing, tileColor);
            }
        }
    }

    // draw cursor
    DrawRectangle(ctx->grid.x * ctx->grid.spacing, ctx->grid.y * ctx->grid.spacing,
                  ctx->grid.spacing, ctx->grid.spacing, cursorColor);

    // draw grid lines
    for(int x = 0; x <= ctx->grid.width * ctx->grid.spacing; x += ctx->grid.spacing)
    {
        // calculate color points
        if(x == (ctx->grid.width >> 1) * ctx->grid.spacing)
            DrawLine(x, 0, x, ctx->grid.height * ctx->grid.spacing, median);
        else if((x & ctx->grid.highlightDivs - 1) == 0)
            DrawLine(x, 0, x, ctx->grid.height * ctx->grid.spacing, major);
        else
            DrawLine(x, 0, x, ctx->grid.height * ctx->grid.spacing, minor);
    }

    for(int y = 0; y <= ctx->grid.height * ctx->grid.spacing; y += ctx->grid.spacing)
    {
        if(y == (ctx->grid.height >> 1) * ctx->grid.spacing)
            DrawLine(0, y, ctx->grid.width * ctx->grid.spacing, y, median);
        else if((y & ctx->grid.highlightDivs - 1) == 0)
            DrawLine(0, y, ctx->grid.width * ctx->grid.spacing, y, major);
        else
            DrawLine(0, y, ctx->grid.width * ctx->grid.spacing, y, minor);
    }
}
