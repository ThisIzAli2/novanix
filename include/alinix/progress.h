/**
 * @author Ali Mirmohammad
 * @file progress.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/
/**
 * @abstract:
 *  - Kernel Progress bar.
*/
#ifndef __ALINIX_KERNEL_PROGRESS_H
#define __ALINIX_KERNEL_PROGRESS_H

#include <alinix/types.h>
#include <alinix/gui/directgui.h>

typedef struct {
    int x;
    int y;
    int w;
    int h;

    uint32_t background;
    uint32_t foreground;
    uint32_t borderColor;
} ProgressBar;

static ProgressBar* progressBar;

void ProgressBarInit(ProgressBar *pb, int x_p, int y_p, int width, int height);

#endif /*__ALINIX_KERNEL_PROGRESS_H*/