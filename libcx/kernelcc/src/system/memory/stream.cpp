/**
 * @author Ali Mirmohammad
 * @file stream.cpp
 * @credits Remco123
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
#include <system/memory/stream.h>
#include <system/log.h>
#include <typing.hpp>

using namespace Novanix;
using namespace Novanix::common;
using namespace Novanix::system;

Stream::Stream() {}
Stream::~Stream() {}

char Stream::Read()
{
    Log(Error, "Virtual stream function called");
    return 0;
}

VOID Stream::Write(char byte)
{
    Log(Error, "Virtual stream function called");
}

INTEGER Stream::Available()
{
    Log(Error, "Virtual stream function called");
    return 0;
}