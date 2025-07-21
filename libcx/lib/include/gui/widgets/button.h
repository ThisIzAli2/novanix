/**
 * @author Ali Mirmohammad
 * @file button.h
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
#ifndef __Novanix__GUI__BUTTON_H
#define __Novanix__GUI__BUTTON_H

#include <gui/widgets/control.h>
#include <gui/gui.h>

namespace Novanix
{
    /**
     * A GUI button
    */
    class Button : public Control
    {
    public:
        /**
         * The text of this label
        */
        GUIProperty<char*> label = GUIProperty<char*>(this, 0);

        /**
         * Create a new button with a peice of text
        */
        Button(char* text = 0);

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
        /**
         * Called when mouse enters control
        */
        void OnMouseEnter(int prevX_abs, int prevY_abs, int newX_abs, int newY_abs) override;
        /**
         * Called when mouse leaves control
        */
        void OnMouseLeave(int prevX_abs, int prevY_abs, int newX_abs, int newY_abs) override;
    };
}

#endif