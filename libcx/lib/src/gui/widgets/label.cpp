/**
 * @author Ali Mirmohammad
 * @file label.cpp
 * Credits Remco123
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
#include <gui/widgets/label.h>

using namespace Novanix;

Label::Label(char* text)
: Control(80, 20)
{
    this->text = text;
}

void Label::DrawTo(Canvas* context, int x_abs, int y_abs)
{
    if(this->text)
        context->DrawString(this->font, this->text, x_abs + 2, y_abs + 2, this->textColor);

    for(Control* c : this->childs)
        c->DrawTo(context, x_abs + c->x, y_abs + c->y);
}