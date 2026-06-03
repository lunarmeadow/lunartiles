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

#ifndef _MODES_H
#define _MODES_H

typedef struct ui_context ui_context_t;

// pointer to the view-specific context object...
// this is sort of fragile but I would like to avoid having all the state be directly accessible.
extern void* view_ctx;

extern void (*UpdateMode)(ui_context_t *, void *);
extern void (*DrawMode)(ui_context_t *, void *);

void InitializeModes(void);
void FreeModes(void);

void SelectMode(ui_context_t* ctx);
void PollMode(ui_context_t* ctx);

#endif
