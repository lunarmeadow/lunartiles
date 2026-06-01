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
#include "viewport.h"
#include "tilegrid.h"

void ClampTarget(viewport_state_t* viewport, grid_state_t* grid)
{
    float minX = 0;
    float maxX = (grid->width * grid->spacing);
    float minY = 0;
    float maxY = (grid->height * grid->spacing);

    if(viewport->cam.target.x < minX)
    {
        viewport->cam.target.x = minX;
    }
    if(viewport->cam.target.x > maxX)
    {
        viewport->cam.target.x = maxX;
    }
    if(viewport->cam.target.y < minY)
    {
        viewport->cam.target.y = minY;
    }
    if(viewport->cam.target.y > maxY)
    {
        viewport->cam.target.y = maxY;
    }
}

void CenterViewport(viewport_state_t* viewport, grid_state_t* grid, screen_t* screen)
{
    Vector2 offset = { screen->width / 2, screen->height / 2 };
    viewport->cam.offset = offset;
    viewport->cam.target.x = (grid->width * grid->spacing) / 2.0f;
    viewport->cam.target.y = (grid->height * grid->spacing) / 2.0f;
    viewport->cam.zoom = 1.0f;
}

// adapted from raylib 2d mouse zoom tutorial
void UpdateViewport(viewport_state_t* viewport, grid_state_t* grid, screen_t* screen)
{
    if (IsKeyPressed(KEY_LEFT_BRACKET)) viewport->zoomMode = 0;
    else if (IsKeyPressed(KEY_RIGHT_BRACKET)) viewport->zoomMode = 1;

    if (IsKeyPressed(KEY_R))
    {
        CenterViewport(viewport, grid, screen);
    }

    Vector2 worldCoords = GetScreenToWorld2D(GetMousePosition(), viewport->cam);
    grid->x = worldCoords.x / grid->spacing;
    grid->y = worldCoords.y / grid->spacing;

    // Translate based on mouse right click
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/viewport->cam.zoom);
        viewport->cam.target = Vector2Add(viewport->cam.target, delta);
    }

    if (viewport->zoomMode == SCROLL_ZOOM_MODE)
    {
        // Zoom based on mouse wheel
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), viewport->cam);

            // Set the offset to where the mouse is
            viewport->cam.offset = GetMousePosition();

            // Set the target to match, so that the camera maps the world space point
            // under the cursor to the screen space point under the cursor at any zoom
            viewport->cam.target = mouseWorldPos;

            ClampTarget(viewport, grid);

            // Zoom increment
            // Uses log scaling to provide consistent zoom speed
            float scale = 0.2f*wheel;
            viewport->cam.zoom = Clamp(expf(logf(viewport->cam.zoom)+scale),
                                       viewport->minZoom, viewport->maxZoom);
        }
    }
    else if (viewport->zoomMode == RTCLICK_ZOOM_MODE)
    {
        // Zoom based on mouse right click
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), viewport->cam);

            // Set the offset to where the mouse is
            viewport->cam.offset = GetMousePosition();

            // Set the target to match, so that the camera maps the world space point
            // under the cursor to the screen space point under the cursor at any zoom
            viewport->cam.target = mouseWorldPos;

            ClampTarget(viewport, grid);
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            // Zoom increment
            // Uses log scaling to provide consistent zoom speed
            float deltaX = GetMouseDelta().x;
            float scale = 0.005f*deltaX;
            viewport->cam.zoom = Clamp(expf(logf(viewport->cam.zoom)+scale),
                                       viewport->minZoom, viewport->maxZoom);
        }
    }
}

void InitializeViewport(viewport_state_t* viewport, grid_state_t* grid, screen_t* screen)
{
    viewport->cam.zoom = 1.0f;
    viewport->cam.rotation = 0.0f;

    CenterViewport(viewport, grid, screen);

    viewport->minZoom = 0.0625f;
    viewport->maxZoom = 32.0f;

    viewport->zoomMode = SCROLL_ZOOM_MODE;
}
