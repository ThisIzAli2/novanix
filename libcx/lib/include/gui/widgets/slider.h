/**
 * @author Ali Mirmohammad
 * @file slider.h
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
#ifndef __Novanix__GUI__SLIDER_H
#define __Novanix__GUI__SLIDER_H

#include <gui/widgets/control.h>
#include <gui/property.h>
#include <gui/events.h>
#include <gui/colors.h>

namespace Novanix
{
    class Slider : public Control
    {
    private:
        bool mouseDown = false;
    public:
        GUIProperty<int> minValue = GUIProperty<int>(this, 0);
        GUIProperty<int> maxValue = GUIProperty<int>(this, 0);
        GUIProperty<int> position = GUIProperty<int>(this, 0);
        GUIProperty<uint32_t> knobColor = GUIProperty<uint32_t>(this, Colors::Blue);
        GUIProperty<int> knobSize = GUIProperty<int>(this, 10);

        EventHandlerList<int> OnValueChanged;
    public:    
        Slider(int min = 0, int max = 100, int current = 50);

        // Called when mouse is down on this control
        void OnMouseDown(int x_abs, int y_abs, uint8_t button) override;

        // Called when mouse is up this control
        void OnMouseUp(int x_abs, int y_abs, uint8_t button) override;

        // Called when mouse is moved this control
        void OnMouseMove(int prevX_abs, int prevY_abs, int newX_abs, int newY_abs) override;

        // Called when mouse enters control
        void OnMouseEnter(int prevX_abs, int prevY_abs, int newX_abs, int newY_abs) override;
        
        // Called when mouse leaves control
        void OnMouseLeave(int prevX_abs, int prevY_abs, int newX_abs, int newY_abs) override;

        // Draw this slider
        void DrawTo(Canvas* context, int x_abs, int y_abs) override;
    };
}

#endif