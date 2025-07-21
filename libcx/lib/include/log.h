/**
 * @author Ali Mirmohammad
 * @file log.h
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
#ifndef __NovanixLIB__LOG_H
#define __NovanixLIB__LOG_H

namespace Novanix
{
    enum LogLevel
    {
        Info,
        Warning,
        Error
    };

    /**
     * Send a log message to the system 
    */
    void Log(LogLevel level, char* msg);
    /**
     * Print a message to the standard output stream 
    */
    void Print(const char* __restrict__ format, ...);
}

#endif