/**
 * @author Ali Mirmohammad
 * @file convert.cpp
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
#include <common/convert.h>
#include <common/string.h>
#include <typing.hpp>

using namespace Novanix::common;

INTEGER IsSpace(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

char* Convert::IntToString(INTEGER n)
{
    static char ret[24];
    INTEGER numChars = 0;
    // Determine if integer is negative
    BOOL isNegative = false;
    if (n < 0)
    {
        n = -n;
        isNegative = true;
        numChars++;
    }
    // Count how much space we will need for the string
    INTEGER temp = n;
    do
    {
        numChars++;
        temp /= 10;
    } while (temp);

    ret[numChars] = 0;
    //Add the negative sign if needed
    if (isNegative)
        ret[0] = '-';
    // Copy digits to string in reverse order
    INTEGER i = numChars - 1;
    do
    {
        ret[i--] = n % 10 + '0';
        n /= 10;
    } while (n);
    return ret;
}
char* Convert::IntToString32(uint32_t n)
{
    static char ret[32];
    INTEGER numChars = 0;
    // Count how much space we will need for the string
    INTEGER temp = n;
    do
    {
        numChars++;
        temp /= 10;
    } while (temp);

    ret[numChars] = 0;
    
    // Copy digits to string in reverse order
    INTEGER i = numChars - 1;
    do
    {
        ret[i--] = n % 10 + '0';
        n /= 10;
    } while (n);
    return ret;
}

char* Convert::IntToHexString(uint8_t w)
{
    static const char* digits = "0123456789ABCDEF";
    uint32_t hexSize = sizeof(uint8_t)<<1;
    char* rc = new char[hexSize + 1]; //Terminate string with 0
    MemoryOperations::memset(rc, 0, hexSize + 1);

    for (uint32_t i=0, j=(hexSize-1)*4 ; i<hexSize; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    return rc;
}
char* Convert::IntToHexString(uint16_t w)
{
    static const char* digits = "0123456789ABCDEF";
    uint32_t hexSize = sizeof(uint16_t)<<1;
    char* rc = new char[hexSize + 1]; //Terminate string with 0
    MemoryOperations::memset(rc, 0, hexSize + 1);

    for (uint32_t i=0, j=(hexSize-1)*4 ; i<hexSize; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    return rc;
}
char* Convert::IntToHexString(uint32_t w)
{
    static const char* digits = "0123456789ABCDEF";
    uint32_t hexSize = sizeof(uint32_t)<<1;
    char* rc = new char[hexSize + 1]; //Terminate string with 0
    MemoryOperations::memset(rc, 0, hexSize + 1);

    for (uint32_t i=0, j=(hexSize-1)*4 ; i<hexSize; ++i,j-=4)
        rc[i] = digits[(w>>j) & 0x0f];
    return rc;
}

INTEGER Convert::StringToInt(char* string)
{
    INTEGER result = 0;
    unsigned int digit;
    INTEGER sign;

    while (IsSpace(*string)) {
        string += 1;
    }

    /*
    * Check for a sign.
    */

    if (*string == '-') {
        sign = 1;
        string += 1;
    } else {
        sign = 0;
        if (*string == '+') {
            string += 1;
        }
    }

    for ( ; ; string += 1) {
        digit = *string - '0';
        if (digit > 9) {
            break;
        }
        result = (10*result) + digit;
    }

    if (sign) {
        return -result;
    }
    return result;
}
uint32_t Convert::HexToInt(char* string)
{
    INTEGER length = String::strlen(string);

	if (length>8)
		length = 8;

	INTEGER fact = 1;
    uint32_t result = 0;
	for(int i = length - 1; i >= 0; i--)
	{
		char digit = String::Lowercase(*(string + i));
		if ((digit >= '0' && digit <= '9') || (digit >= 'a' && digit <= 'f'))
		{
			if (digit >= 97)
				result += (digit - 87) * fact;
			else
				result += (digit - 48) * fact;
			fact = fact << 4;
		}
		else
			return 0;
	}
	return result;
}