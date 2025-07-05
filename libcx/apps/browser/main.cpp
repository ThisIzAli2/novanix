/**
 * @author Ali Mirmohammad
 * @file main.cpp
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
#include <new.h>
#include <gui/gui.h>
#include <gui/widgets/button.h>
#include <gui/widgets/control.h>
#include <gui/widgets/scrollbar.h>
#include <gui/widgets/window.h>
#include <gui/directgui.h>
#include <convert.h>
#include <string.h>
#include <log.h>
#include <proc.h>

using namespace Novanix;

Window* mainWindow = 0;

void ValueChanged(void* s, int v)
{
    mainWindow->backColor = v * 1000;
}

int main(int argc, char** argv)
{
    GUI::SetDefaultFont();

    mainWindow = new Window(600, 600, 300, 300);
    mainWindow->titleString = "Novanix File Browser";

    ScrollBar* scroll = new ScrollBar(Vertical);
    scroll->x = 100;
    scroll->y = 200;
    scroll->value.onChanged += ValueChanged;
    mainWindow->AddChild(scroll);

    while (GUI::HasItems()) {
        GUI::DrawGUI();
        GUI::ProcessEvents();
        //scroll->value += 1;
        if(scroll->value >= scroll->maxValue) {
            scroll->value = 0;
            scroll->maxValue += 20;
        }
    }

    return 0;
}