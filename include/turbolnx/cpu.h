#pragma once 
#include <cstdint>
namespace turbolnx {
    struct CpuStats{
        uint64_t usagePercentage;
        uint64_t total;
        uint64_t idle;
        uint64_t temp;
    };
    void initcpustats(CpuStats *cpustat);
    void getCpuStats(CpuStats *prevcpustats);
}
