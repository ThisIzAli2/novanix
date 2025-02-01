#pragma once

#include <keymap.hpp>
#include <system/log.h>
#include <system/bootconsole.h>
#include <common/string.h>
#include <help.hpp>
#include <typing.hpp>
#include <shutdownsys.h>
#include <buffer.h>
#include <putchar.h>
#include <novanix/dir.h>
#include <novanix/user.h>
#include <novanix/access.h>
#include <novanix/time/time.hpp>


namespace Novanix{
    namespace fs{
        enum class Permission {
        READ = 1,
        WRITE = 2,
        EXECUTE = 4
    };
    }
}
