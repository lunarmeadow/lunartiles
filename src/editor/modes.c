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
#include "raygui.h"
#include "state.h"
#include "../ui/context.h"

void (*UpdateMode)(ui_context_t *);
void (*DrawMode)(ui_context_t *);

void UpdateEditMode(ui_context_t* ctx)
{
    UpdateViewport(ctx);
}
void DrawEditMode(ui_context_t* ctx)
{
    BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        BeginMode2D(ctx->viewport.cam);
            DrawTileGrid(ctx);
        EndMode2D();
    EndDrawing();
}

void PollMode(editor_state_t* state)
{
    switch(state->view_mode)
    {
        case EDIT:
            UpdateMode = &UpdateEditMode;
            DrawMode = &DrawEditMode;
            break;
        case PROPERTIES:
            break;
        case MAPINFO:
            break;
        case COMMAND:
            break;
    }
}
