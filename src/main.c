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

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "style_lavanda.h"

#include "ui/tilegrid.h"
#include "ui/screen.h"
#include "ui/viewport.h"

int main()
{
    grid_state_t grid;
    screen_t screen;
    viewport_state_t viewport;

    InitializeTileGrid(&grid, 128, 128, 16, 4);
    InitializeScreen(&screen, 1280, 720, 60);
    InitializeViewport(&viewport);

    GuiLoadStyleLavanda();

    while (!WindowShouldClose())
    {
        // update all editor state before draw
        UpdateViewport(&viewport, &grid, &screen);

        // draw everything
        BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
            BeginMode2D(viewport.cam);
                DrawTileGrid(&grid);
            EndMode2D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
