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

#include "raylib.h"
#include "ui/context.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "style_lavanda.h"

#include "ui/tilegrid.h"
#include "ui/screen.h"
#include "ui/viewport.h"

int main()
{
    ui_context_t ctx;

    InitializeUIContext(&ctx);
    GuiLoadStyleLavanda();

    while (!WindowShouldClose())
    {
        // update all editor state before draw
        UpdateViewport(&ctx);

        // draw everything
        BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
            BeginMode2D(ctx.viewport.cam);
                DrawTileGrid(&ctx);
            EndMode2D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
