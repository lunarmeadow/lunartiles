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

void InitializeScreen(void)
{
    InitWindow(0, 0, "lunartiles");
    int w = GetScreenWidth() - 100;
    int h = GetScreenHeight() - 200;

    ToggleFullscreen();
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(800, 600);
    SetWindowSize(w, h);
    SetWindowPosition(50, 100);

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
}
