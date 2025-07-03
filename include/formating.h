/**
 * @author Ali Mirmohammad
 * @file formating.h
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

#ifndef __FORMATING_H_NOVA
#define __FORMATING_H_NOVA

#include <common/types.h>
#include <statements.h>


DECLARE_NAME_SPACE

uint8_t binary_to_bcd(uint8_t bin) {
    return ((bin / 10) << 4) | (bin % 10);
}



#endif // __FORMATING_H_NOVA