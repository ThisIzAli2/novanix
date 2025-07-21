/**
 * @author Ali Mirmohammad
 * @file listinterview.h
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
#ifndef __Novanix__GUI__LISTVIEW_H
#define __Novanix__GUI__LISTVIEW_H

#include <gui/widgets/control.h>
#include <imaging/image.h>
#include <gui/gui.h>

namespace Novanix
{
    class ListViewItem
    {
    public:
        char* title;
        Imaging::Image* icon;
    public:
        ListViewItem();
        ~ListViewItem();
    };

    class ListView : public Control
    {
    private:
        List<ListViewItem> items;
    public:
        ListView();
        ~ListView();

        /**
         * Draw this button
        */
        void DrawTo(Canvas* context, int x_abs, int y_abs) override;

    /*/////////
    // Events
    *//////////
    friend class Window;
    friend class Context;
    protected:
        /**
         * Called when mouse is down on control
        */
        void OnMouseDown(int x_abs, int y_abs, uint8_t button) override;
        /**
         * Called when mouse is up on control
        */
        void OnMouseUp(int x_abs, int y_abs, uint8_t button) override;
    };
}

#endif