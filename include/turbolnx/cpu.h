#pragma once 
#include <cstdint>
namespace turbolnx {
    struct CpuStats{
        uint64_t usagePercentage;
        uint64_t total;
        uint64_t idle;
    };
    void initcpustats(CpuStats *cpustat);
    void getCpuStats(CpuStats *prevcpustats);
}
