#include <api.h>

#include <syscall.h>
#include <log.h>
#include <proc.h>

using namespace Novanix;

void API::Initialize()
{
    //Call kernel to set this process as a Novanix process
    Process::ID = DoSyscall(SYSCALL_SET_Novanix_LIB);

    Log(Info, "Novanix API Initialized for this process");
}