/**
 * @author Ali Mirmohammad
 * @file progress.h
 * @Credits Remco123
 ** This file is part of Novanix.

**Novanix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**Novanix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with Novanix. If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef PROGRESS_H
#define PROGRESS_H

#include <types.h>
#include <gui/directgui.h>

using namespace Novanix;

class ProgressBar
{
private:
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    uint32_t background = 0xFFFFFFFF;
    uint32_t foreground = 0xFF00FF00;
    uint32_t borderColor = 0xFF000000;
public:
    ProgressBar(int x_p, int y_p, int width, int height);

    void SetValue(int v);
};

ProgressBar::ProgressBar(int x_p, int y_p, int width, int height)
{
    this->x = x_p;
    this->y = y_p;
    this->w = width;
    this->h = height;
}

void ProgressBar::SetValue(int v)
{
    DirectGUI::DrawFillRect(background, x, y, w + 1, h);
    DirectGUI::DrawRect(borderColor, x, y, w, h);
    if(v == 0)
        return;

    double fraction = (v/100.0);
    DirectGUI::DrawFillRect(foreground, x + 1, y + 1, (fraction * (double)w), h - 1);
}

#endif