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

#include "ui/context.h"
#include "ui/modes.h"

#define STB_DS_IMPLEMENTATION
#include "stb/stb_ds.h"

int main()
{
    ui_context_t ui_ctx;

    InitializeUIContext(&ui_ctx);
    InitializeModes();

    GuiLoadStyleLavanda();

    PollMode(&ui_ctx);

    while (!WindowShouldClose())
    {
        SelectMode(&ui_ctx);

        if(view_ctx == nullptr)
            break;

        UpdateMode(&ui_ctx, view_ctx);
        DrawMode(&ui_ctx, view_ctx);
    }

    FreeModes();
    FreeUIContext(&ui_ctx);

    CloseWindow();
    return 0;
}
