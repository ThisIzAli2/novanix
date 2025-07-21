/**
 * @author Ali Mirmohammad
 * @file scrollbox.h
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
#ifndef __Novanix__GUI__SCROLLBOX_H
#define __Novanix__GUI__SCROLLBOX_H

#include <gui/widgets/control.h>
#include <gui/widgets/scrollbar.h>

namespace Novanix
{
    class ScrollBox : public Control
    {
    public:
        ScrollBar* scrollVertical = 0;
        ScrollBar* scrollHorizontal = 0;
    public:
        ScrollBox();

        // Draw this scrollbox
        void DrawTo(Canvas* context, int x_abs, int y_abs) override;
    };
}

#endif