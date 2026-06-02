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

#ifndef _EDITORSTATE_H
#define _EDITORSTATE_H

// edit = grid editor view
// properties = editor for selected tile attributes or,
// if none selected, the attributes future tiles will use.
// mapinfo = edit map fields such as size, description
// command = used for things like navigating when doing file i/o
enum editor_mode {
    EDIT, PROPERTIES, MAPINFO, COMMAND
};

typedef struct {
    enum editor_mode mode;
} editor_state_t;

#endif
