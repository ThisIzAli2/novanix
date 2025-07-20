/**
 * @author Ali Mirmohammad
 * @file terminal.h
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

#ifndef _HEISEN_TERMINAL_H
#define _HEISEN_TERMINAL_H

#include <heisen/typing.h>

class StringView;


enum class NumberFormat{
    Decimal,
    DecimalNoCommas,
    Hexa
};

class Printer{
    public:
        Printer();
        /*Print a single character*/
        Printer& operator<<(char c);

        Printer& operator<<(const char* str);
        Printer& operator <<(const StringView& str);

        // Prints an signed int.
        Printer& operator <<(int c);

        // Prints a long int.
        Printer& operator <<(size_t num);

        // Switches to a new number format.
        Printer& operator <<(NumberFormat format);
    
    private:
        void PrintHexidecimal(size_t number);
        void PrintDecimal(size_t number, bool with_commas);

        // The current number format.
        NumberFormat number_format_;
};

extern Printer print;

// Initializes the text printer.
extern void InitializePrinter();


#endif // _HEISEN_TERMINAL_H