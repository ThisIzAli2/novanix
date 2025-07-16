/**
 * @author Ali Mirmohammad
 * @file datetime.cpp
 * Credits Remco123
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
#include <datetime.h>
#include <syscall.h>
#include <types.h>
#include <convert.h>
#include <string.h>
#include <log.h>

using namespace Novanix;

DateTime DateTime::Current()
{
    DateTime result;
    DoSyscall(SYSCALL_GET_DATETIME, (uint32_t)&result);
    return result;
}

char* DateTime::ToString()
{
    char* fakeSecondsPtr = Convert::IntToString(this->Seconds); int fakeSecondsLen = 2; char* SecondsPtr = new char[2]; if(strlen(fakeSecondsPtr) == 1) { SecondsPtr[0] = '0'; SecondsPtr[1] = fakeSecondsPtr[0]; } else { memcpy(SecondsPtr, fakeSecondsPtr, fakeSecondsLen); }
    char* fakeMinutesPtr = Convert::IntToString(this->Minutes); int fakeMinutesLen = 2; char* MinutesPtr = new char[2]; if(strlen(fakeMinutesPtr) == 1) { MinutesPtr[0] = '0'; MinutesPtr[1] = fakeMinutesPtr[0]; } else { memcpy(MinutesPtr, fakeMinutesPtr, fakeMinutesLen); }
    char* fakeHoursPtr = Convert::IntToString(this->Hours); int fakeHoursLen = 2; char* HoursPtr = new char[2]; if(strlen(fakeHoursPtr) == 1) { HoursPtr[0] = '0'; HoursPtr[1] = fakeHoursPtr[0]; } else { memcpy(HoursPtr, fakeHoursPtr, fakeHoursLen); }

    char* fakeDayPtr = Convert::IntToString(this->Day); int fakeDayLen = 2; char* DayPtr = new char[2]; if(strlen(fakeDayPtr) == 1) { DayPtr[0] = '0'; DayPtr[1] = fakeDayPtr[0]; } else { memcpy(DayPtr, fakeDayPtr, fakeDayLen); }
    char* fakeMonthPtr = Convert::IntToString(this->Month); int fakeMonthLen = 2; char* MonthPtr = new char[2]; if(strlen(fakeMonthPtr) == 1) { MonthPtr[0] = '0'; MonthPtr[1] = fakeMonthPtr[0]; } else { memcpy(MonthPtr, fakeMonthPtr, fakeMonthLen); }
    char* fakeYearPtr = Convert::IntToString(this->Year); int fakeYearLen = strlen(fakeYearPtr); char* YearPtr = new char[fakeYearLen]; memcpy(YearPtr, fakeYearPtr, fakeYearLen);

    //                Day-Month-Year Seconds-Minute-Hour
    int totalLength = fakeDayLen + 1 + fakeMonthLen + 1 + fakeYearLen + 1 + fakeSecondsLen + 1 + fakeMinutesLen + 1 + fakeHoursLen;

    static char resultBuffer[60];
    memset(resultBuffer, 0, 60);

    char* resultPointer = resultBuffer;
    memcpy(resultPointer, YearPtr, fakeYearLen);
    resultPointer += fakeYearLen;
    *resultPointer++ = '-';

    memcpy(resultPointer, MonthPtr, fakeMonthLen);
    resultPointer += fakeMonthLen;
    *resultPointer++ = '-';

    memcpy(resultPointer, DayPtr, fakeDayLen);
    resultPointer += fakeDayLen;
    *resultPointer++ = ' ';

    memcpy(resultPointer, HoursPtr, fakeHoursLen);
    resultPointer += fakeHoursLen;
    *resultPointer++ = ':';

    memcpy(resultPointer, MinutesPtr, fakeMinutesLen);
    resultPointer += fakeMinutesLen;
    *resultPointer++ = ':';

    memcpy(resultPointer, SecondsPtr, fakeSecondsLen);
    resultPointer += fakeSecondsLen;

    //CleanUp
    delete SecondsPtr;
    delete MinutesPtr;
    delete HoursPtr;
    delete DayPtr;
    delete MonthPtr;
    delete YearPtr;

    resultBuffer[totalLength] = '\0';

    return resultBuffer;
}