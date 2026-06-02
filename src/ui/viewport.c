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
#include "raymath.h"
#include "context.h"

void ClampTarget(ui_context_t* ctx)
{
    float minX = 0;
    float maxX = (ctx->grid.width * ctx->grid.spacing);
    float minY = 0;
    float maxY = (ctx->grid.height * ctx->grid.spacing);

    if(ctx->viewport.cam.target.x < minX)
    {
        ctx->viewport.cam.target.x = minX;
    }
    if(ctx->viewport.cam.target.x > maxX)
    {
        ctx->viewport.cam.target.x = maxX;
    }
    if(ctx->viewport.cam.target.y < minY)
    {
        ctx->viewport.cam.target.y = minY;
    }
    if(ctx->viewport.cam.target.y > maxY)
    {
        ctx->viewport.cam.target.y = maxY;
    }
}

void CenterViewport(ui_context_t* ctx)
{
    Vector2 offset = { ctx->screen.width / 2.0f, ctx->screen.height / 2.0f };
    ctx->viewport.cam.offset = offset;
    ctx->viewport.cam.target.x = (ctx->grid.width * ctx->grid.spacing) / 2.0f;
    ctx->viewport.cam.target.y = (ctx->grid.height * ctx->grid.spacing) / 2.0f;
    ctx->viewport.cam.zoom = 1.0f;
}

// adapted from raylib 2d mouse zoom tutorial
void UpdateViewport(ui_context_t* ctx)
{
    if (IsKeyPressed(KEY_LEFT_BRACKET)) ctx->viewport.zoomMode = 0;
    else if (IsKeyPressed(KEY_RIGHT_BRACKET)) ctx->viewport.zoomMode = 1;

    if (IsKeyPressed(KEY_R))
    {
        CenterViewport(ctx);
    }

    Vector2 worldCoords = GetScreenToWorld2D(GetMousePosition(), ctx->viewport.cam);
    ctx->grid.x = worldCoords.x / ctx->grid.spacing;
    ctx->grid.y = worldCoords.y / ctx->grid.spacing;

    // Translate based on mouse right click
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/ctx->viewport.cam.zoom);
        ctx->viewport.cam.target = Vector2Add(ctx->viewport.cam.target, delta);
    }

    if (ctx->viewport.zoomMode == SCROLL_ZOOM_MODE)
    {
        // Zoom based on mouse wheel
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), ctx->viewport.cam);

            // Set the offset to where the mouse is
            ctx->viewport.cam.offset = GetMousePosition();

            // Set the target to match, so that the camera maps the world space point
            // under the cursor to the screen space point under the cursor at any zoom
            ctx->viewport.cam.target = mouseWorldPos;

            ClampTarget(ctx);

            // Zoom increment
            // Uses log scaling to provide consistent zoom speed
            float scale = 0.2f*wheel;
            ctx->viewport.cam.zoom = Clamp(expf(logf(ctx->viewport.cam.zoom)+scale),
                                       ctx->viewport.minZoom, ctx->viewport.maxZoom);
        }
    }
    else if (ctx->viewport.zoomMode == RTCLICK_ZOOM_MODE)
    {
        // Zoom based on mouse right click
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), ctx->viewport.cam);

            // Set the offset to where the mouse is
            ctx->viewport.cam.offset = GetMousePosition();

            // Set the target to match, so that the camera maps the world space point
            // under the cursor to the screen space point under the cursor at any zoom
            ctx->viewport.cam.target = mouseWorldPos;

            ClampTarget(ctx);
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            // Zoom increment
            // Uses log scaling to provide consistent zoom speed
            float deltaX = GetMouseDelta().x;
            float scale = 0.005f*deltaX;
            ctx->viewport.cam.zoom = Clamp(expf(logf(ctx->viewport.cam.zoom)+scale),
                                       ctx->viewport.minZoom, ctx->viewport.maxZoom);
        }
    }
}

void InitializeViewport(ui_context_t* ctx)
{
    ctx->viewport.cam.zoom = 1.0f;
    ctx->viewport.cam.rotation = 0.0f;

    CenterViewport(ctx);

    ctx->viewport.minZoom = 0.0625f;
    ctx->viewport.maxZoom = 32.0f;

    ctx->viewport.zoomMode = SCROLL_ZOOM_MODE;
}
