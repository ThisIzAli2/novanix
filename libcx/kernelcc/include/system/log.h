#ifndef __Novanix__SYSTEM__LOG_H
#define __Novanix__SYSTEM__LOG_H

#include <common/types.h>
#include <system/bootconsole.h>

namespace Novanix
{
    namespace system
    {
        #define LOG_SHOW_MS 1

        enum LogLevel
        {
            Info,
            Warning,
            Error
        };

        void Log(LogLevel level, const char* __restrict__ format, ...);
        void Print(const char* data, common::uint32_t length);
        void printk(enum vga_color color, const char* __restrict__ format, ...);
    }
}

#endif