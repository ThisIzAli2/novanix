/**
 * @author Ali Mirmohammad
 * @file item.h
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
#ifndef ITEM_H
#define ITEM_H

#include <gui/context.h>
#include <gui/gui.h>
#include <imaging/image.h>
#include <imaging/pngformat.h>

using namespace Novanix;
using namespace Novanix::Imaging;

class DesktopItem : Rectangle
{
public:
    Context* context;
    char* label;
    bool drawLabel;
    char* filename;
    uint8_t* iconBuffer;
    DesktopItem(int x, int y, int width, int height);

    void DrawToContext();
};

DesktopItem::DesktopItem(int x, int y, int width, int height)
: Rectangle(width, height, x, y) {
    this->context = GUI::RequestContext(width, height, x, y);
    this->context->canvas->Clear();
    this->context->sharedContextInfo->background = true;
    this->context->sharedContextInfo->supportsTransparency = true;
    this->context->sharedContextInfo->supportsDirtyRects = true;
}

void DesktopItem::DrawToContext()
{
    if(this->iconBuffer)
    {
        Image* img = PNGDecoder::ConvertRAW(this->iconBuffer);
        if(img) {
            uint32_t* src = img->GetBufferPtr();
            for(int x = 0; x < img->GetWidth(); x++)
                for(int y = 0; y < img->GetHeight(); y++) {
                    uint32_t argb = src[y * img->GetWidth() + x];
                    this->context->canvas->SetPixel(x, y, argb);
                }
        }
        else
            this->context->canvas->Clear(Colors::Black);
    }
    if(this->drawLabel) {
        this->context->canvas->DrawRect(0xFF000000, 0, height-20, width-1, 20-1);
        this->context->canvas->DrawString(GUI::defaultFont, this->label, 5, height-17, 0xFFFFFFFF);
    }
    this->context->sharedContextInfo->AddDirtyArea(0, 0, width, height);
}

#endif