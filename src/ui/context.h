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

#ifndef _BLANK_H
#define _BLANK_H

#include "tilegrid.h"
#include "screen.h"
#include "viewport.h"

typedef struct ui_context {
    grid_state_t grid;
    screen_t screen;
    viewport_state_t viewport;
} ui_context_t;

void InitializeUIContext(ui_context_t* ctx);

#endif
