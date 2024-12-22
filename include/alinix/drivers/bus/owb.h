/**
 * @file owb.h
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
 * @abstraction:
 *  - Driver stuff.
*/
#ifndef __ALINIX_DRIVERS_BUS_OWB_H
#define __ALINIX_DRIVERS_BUS_OWB_H

// ROM commands
#define OWB_ROM_SEARCH        0xF0  ///< Perform Search ROM cycle to identify devices on the bus
#define OWB_ROM_READ          0x33  ///< Read device ROM (single device on bus only)
#define OWB_ROM_MATCH         0x55  ///< Address a specific device on the bus by ROM
#define OWB_ROM_SKIP          0xCC  ///< Address all devices on the bus simultaneously
#define OWB_ROM_SEARCH_ALARM  0xEC  ///< Address all devices on the bus with a set alarm flag


#endif //  __ALINIX_DRIVERS_BUS_OWB_H