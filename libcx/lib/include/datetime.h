/**
 * @author Ali Mirmohammad
 * @file datetime.h
 * @credits remco123
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
#ifndef __Novanix__DATETIME_H
#define __Novanix__DATETIME_H

namespace Novanix
{
    class DateTime
    {
    public:
        signed char Day = -1;
        signed char Month = -1;
        int Year = -1;

        signed char Seconds = -1;
        signed char Minutes = -1;
        signed char Hours = -1;

        /**
         * Get the current date and time of this system
        */
        static DateTime Current();

        /**
         * Convert DateTime into a readable string
        */
        char* ToString();
    };
}

#endif