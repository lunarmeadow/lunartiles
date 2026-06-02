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

#ifndef _VIEWPORT_H
#define _VIEWPORT_H

#define SCROLL_ZOOM_MODE 0
#define RTCLICK_ZOOM_MODE 1

#include "raylib.h"

typedef struct edit_context edit_context_t;

typedef struct {
    Camera2D cam;
    float minZoom, maxZoom;
    int zoomMode;
} viewport_state_t;

void UpdateViewport(edit_context_t* ctx);
void InitializeViewport(edit_context_t* ctx);

#endif
