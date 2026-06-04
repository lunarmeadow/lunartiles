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

#include "modes.h"
#include "edit/tilegrid.h"
#include "raylib.h"
#include "raygui.h"
#include "../ui/context.h"

void* view_ctx;

void (*UpdateMode)(ui_context_t *, void *);
void (*DrawMode)(ui_context_t *, void *);

// do not access directly! these are dynamically injected
static edit_context_t edit;
static props_context_t props;
static mapinfo_context_t mapinfo;
static cmd_context_t cmd;

// private mode init/free

void InitializeEditMode(void)
{
    InitializeTileGrid(&edit, 128, 128, 32, 4);
    InitializeViewport(&edit);
}

void FreeEditMode(void)
{
    FreeTileGrid(&edit);
}

// mode init/free public interface

void InitializeModes(void)
{
    InitializeEditMode();
}

void FreeModes(void)
{
    FreeEditMode();
}

// private update/draw funcs

void UpdateEditMode(ui_context_t* ui_ctx, void* edit_ctx)
{
    edit_context_t* ctx = (edit_context_t*)edit_ctx;
    ProcessTiles(ctx);
    UpdateViewport(ui_ctx, ctx);
}
void DrawEditMode(ui_context_t* ui_ctx, void* edit_ctx)
{
    edit_context_t* ctx = (edit_context_t*)edit_ctx;
    BeginDrawing();
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        BeginMode2D(ctx->viewport.cam);
            DrawTileGrid(ui_ctx, ctx);
        EndMode2D();
    EndDrawing();
}

void UpdatePropertiesMode(ui_context_t* ui_ctx, void* props_ctx)
{
    props_context_t* ctx = (props_context_t*)props_ctx;
}
void DrawPropertiesMode(ui_context_t* ui_ctx, void* props_ctx)
{
    props_context_t* ctx = (props_context_t*)props_ctx;
    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        DrawText("Property Mode", 0, 0, 48, GetColor(0xff0000ff));
    EndDrawing();
}

void UpdateMapinfoMode(ui_context_t* ui_ctx, void* mapinfo_ctx)
{
    mapinfo_context_t* ctx = (mapinfo_context_t*)mapinfo_ctx;
}
void DrawMapinfoMode(ui_context_t* ui_ctx, void* mapinfo_ctx)
{
    mapinfo_context_t* ctx = (mapinfo_context_t*)mapinfo_ctx;
    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    DrawText("Map Info Mode", 0, 0, 48, GetColor(0xff0000ff));
    EndDrawing();
}

void UpdateCommandMode(ui_context_t* ui_ctx, void* cmd_ctx)
{
    cmd_context_t* ctx = (cmd_context_t*)cmd_ctx;
}
void DrawCommandMode(ui_context_t* ui_ctx, void* cmd_ctx)
{
    cmd_context_t* ctx = (cmd_context_t*)cmd_ctx;
    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    DrawText("Command Mode", 0, 0, 48, GetColor(0xff0000ff));
    EndDrawing();
}

void SelectMode(ui_context_t* ctx)
{
    if(IsKeyDown(KEY_LEFT_CONTROL))
    {
        if(IsKeyPressed(KEY_ONE))
        {
            ctx->view_mode = EDIT;
            PollMode(ctx);
        }
        if(IsKeyPressed(KEY_TWO))
        {
            ctx->view_mode = PROPERTIES;
            PollMode(ctx);
        }
        if(IsKeyPressed(KEY_THREE))
        {
            ctx->view_mode = MAPINFO;
            PollMode(ctx);
        }
        if(IsKeyPressed(KEY_FOUR))
        {
            ctx->view_mode = COMMAND;
            PollMode(ctx);
        }
    }
}

void PollMode(ui_context_t* ctx)
{
    switch(ctx->view_mode)
    {
        case EDIT:
            UpdateMode = &UpdateEditMode;
            DrawMode = &DrawEditMode;
            view_ctx = &edit;
            break;
        case PROPERTIES:
            UpdateMode = &UpdatePropertiesMode;
            DrawMode = &DrawPropertiesMode;
            view_ctx = &props;
            break;
        case MAPINFO:
            UpdateMode = &UpdateMapinfoMode;
            DrawMode = &DrawMapinfoMode;
            view_ctx = &mapinfo;
            break;
        case COMMAND:
            UpdateMode = &UpdateCommandMode;
            DrawMode = &DrawCommandMode;
            view_ctx = &cmd;
            break;
        default:
            UpdateMode = &UpdateEditMode;
            DrawMode = &DrawEditMode;
            view_ctx = &edit;
            break;
    }
}
