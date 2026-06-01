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

#include "context.h"
#include "raylib.h"
#include "raygui.h"
#include <math.h>

void InitializeTileGrid(ui_context_t* ctx, int w, int h, int spacing, int divs)
{
    ctx->grid.width = w;
    ctx->grid.height = h;
    ctx->grid.spacing = spacing;
    ctx->grid.highlightDivs = divs * spacing;
}

void DrawTileGrid(ui_context_t* ctx)
{
    // derived from lavanda line color
    Color minor = GetColor(0x6374a0ff);
    Color major = GetColor(0x7184b7ff);
    Color median = GetColor(0x67b7b2ff);

    Color cur;

    for(int x = 0; x <= ctx->grid.width * ctx->grid.spacing; x += ctx->grid.spacing)
    {
        // calculate color points
        if(x == round(ctx->grid.width / 2.0f) * ctx->grid.spacing)
            cur = median;
        else if(x % ctx->grid.highlightDivs == 0)
            cur = major;
        else
            cur = minor;

        DrawLine(x, 0, x, ctx->grid.height * ctx->grid.spacing, cur);
    }

    for(int y = 0; y <= ctx->grid.height * ctx->grid.spacing; y += ctx->grid.spacing)
    {
        if(y == round(ctx->grid.height / 2.0f) * ctx->grid.spacing)
            cur = median;
        else if(y % ctx->grid.highlightDivs == 0)
            cur = major;
        else
            cur = minor;

        DrawLine(0, y, ctx->grid.width * ctx->grid.spacing, y, cur);
    }

    DrawRectangle(ctx->grid.x * ctx->grid.spacing, ctx->grid.y * ctx->grid.spacing,
                  ctx->grid.spacing, ctx->grid.spacing, median);
}
