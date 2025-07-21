/**
 * @author Ali Mirmohammad
 * @file image.h
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
#ifndef __NovanixLIB__IMAGING_IMAGE_H
#define __NovanixLIB__IMAGING_IMAGE_H

#include <types.h>
#include <gui/canvas.h>

namespace Novanix
{
    namespace Imaging
    {
        // Enable alpha for bilinear image scaling or not?
        #define BILINEAR_ALPHA 1

        enum ResizeMethod
        {
            NearestNeighbor,
            Bilinear
        };

        class Image
        {
        private:
            int width = 0;
            int height = 0;
            Canvas* canvas = 0;

            uint32_t* buffer = 0;
        public:
            // Create new image using a width and height
            Image(const int width, const int height);
            // Destructor
            ~Image();

            // Generate a canvas for this image and return it
            // It will only get generated once for each image and will get destroyed automatically
            Canvas* GetCanvas();

            // Get width of image
            int GetWidth();

            // Get height of image
            int GetHeight();

            // Receive pointer to raw buffer
            uint32_t* GetBufferPtr();

            // Draw this image directly to a canvas
            void DrawTo(Canvas* target, int x = 0, int y = 0);

            // Create image from a file present on disk
            static Image* CreateFromFile(const char* filepath, const char* ext = 0);

            // Resize source image and return result
            static Image* Resize(Image* source, int newWidth, int newHeight, ResizeMethod method = NearestNeighbor);
        private:
            static Image* ResizeNearestNeighbor(Image* source, int newWidth, int newHeight);
            static Image* ResizeBilinear(Image* source, int newWidth, int newHeight);
        };
    }
}

#endif