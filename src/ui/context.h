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

#ifndef _CONTEXT_H
#define _CONTEXT_H


#include "screen.h"
#include "edit/viewport.h"
#include "edit/tilegrid.h"

// edit = grid editor view
// properties = editor for selected tile attributes or,
// if none selected, the attributes future tiles will use.
// mapinfo = edit map fields such as size, description
// command = used for things like navigating when doing file i/o
enum editor_mode {
    EDIT, PROPERTIES, MAPINFO, COMMAND
};

enum move_mode {
    KEYBOARD, MOUSE
};

typedef struct ui_context {
    enum editor_mode view_mode;
    enum move_mode move_mode;

    tile_t propertyTile; // tile to use for modifying selected tiles or adding new tiles
    tile_t** selectedTiles; // tile selection buffer (using stb_ds)
} ui_context_t;

typedef struct edit_context {
    grid_state_t grid;
    viewport_state_t viewport;
} edit_context_t;

typedef struct props_context {
    int placeholder;
} props_context_t;

typedef struct mapinfo_context {
    int placeholder;
} mapinfo_context_t;

typedef struct cmd_context {
    int placeholder;
} cmd_context_t;

void InitializeUIContext(ui_context_t* ctx);
void FreeUIContext(ui_context_t* ctx);

#endif
