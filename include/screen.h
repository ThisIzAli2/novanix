/**
 * @author Ali Mirmohammad
 * @file screen.h
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
#ifndef _HEISEN_SCREEN_H
#define _HEISEN_SCREEN_H

#include <typing.hpp>

VOID InitScreen();
VOID PutPixel(INTEGER X,INTEGER Y,INTEGER RGB);
VOID PutRect(INTEGER X,INTEGER Y,INTEGER Width,INTEGER Height,INTEGER RGB);
VOID PutLine(INTEGER X1, INTEGER Y1, INTEGER X2, INTEGER Y2, INTEGER RGB);


#endif // _HEISEN_SCREEN_H