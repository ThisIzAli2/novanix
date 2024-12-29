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