#pragma once 
#include <string>

namespace turbolnx {
    struct MemoryStatistics{
        double totalMemory;
        double memoryUsed;
        double memoryAvailaible;
        double memoryCached;
        double swapTotal;
        double swapFree;
        double swapUsed;

        std::string memTotalFormat;
        std::string memUsedFormat;
        std::string memAvailFormat;
        std::string memCachedFormat;
        std::string swapTotalFormat;
        std::string swapUsedFormat;
        std::string swapFreeFormat;
    };

    MemoryStatistics getMemoryStatistics();
}
