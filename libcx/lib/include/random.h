#ifndef Novanix__RANDOM_H
#define Novanix__RANDOM_H

#include <types.h>

namespace Novanix
{
    class Random
    {
    public:
        static int Next(uint32_t max = 32767);
        static int Next(uint32_t min, uint32_t max);             
        static void SetSeed(uint32_t seed);
    };
}

#endif