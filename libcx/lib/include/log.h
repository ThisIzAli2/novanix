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