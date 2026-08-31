#include "turbolnx/memory.h"
#include <cstdint>
#include <fstream>
#include <string>

namespace {
    struct formattedValue{
        double value;
        std::string format;
    };

    formattedValue formatMemOut(uint64_t inputval){
       if (inputval<1024ULL) {
           return formattedValue{.value = static_cast<double>(inputval),.format = "KiB"};
       }
       else if (inputval < 1024ULL*1024) {
           return formattedValue{.value = static_cast<double>(inputval/1024.0),.format = "MiB"}; 
       }
       else if (inputval < 1024ULL*1024*1024) {
           return formattedValue{.value = static_cast<double>(inputval/(1024.0*1024.0)),.format = "GiB"};
       }
       else{
           return formattedValue{.value = static_cast<double>(inputval)/(1024.0*1024.0*1024.0),.format = "TiB"};
       }
    }   
}

turbolnx::MemoryStatistics turbolnx::getMemoryStatistics(){
    std::ifstream memoryinfo("/proc/meminfo");
    std::string name;
    uint64_t value;
    std::string formatThrowAway;
    MemoryStatistics memstats{};
    uint64_t totalMemory = 0; 
    uint64_t availableMemory = 0;
    uint64_t swapTotal = 0;
    uint64_t swapFree = 0;
    uint64_t memUsed = 0;
    uint64_t swapUsed = 0;
    while(memoryinfo>>name>>value>>formatThrowAway){
        if(name == "MemTotal:"){
            totalMemory = value;
            auto format = formatMemOut(value);
            memstats.totalMemory = format.value;
            memstats.memTotalFormat = format.format;
        }
        else if(name == "MemAvailable:"){
            availableMemory = value;
            auto format = formatMemOut(value);
            memstats.memoryAvailaible = format.value;
            memstats.memAvailFormat = format.format;
        }
        else if (name == "Cached:") {
            auto format = formatMemOut(value);
            memstats.memoryCached = format.value;
            memstats.memCachedFormat = format.format;
        }
        else if (name == "SwapTotal:") {
            swapTotal = value;
            auto format = formatMemOut(value);
            memstats.swapTotal = format.value;
            memstats.swapTotalFormat = format.format;
        }
        else if (name == "SwapFree:") {
            swapFree = value;
            auto format = formatMemOut(value);
            memstats.swapFree = format.value;
            memstats.swapFreeFormat = format.format;
        }
    }
    memUsed = totalMemory - availableMemory;
    swapUsed = swapTotal - swapFree;
    auto muformat = formatMemOut(memUsed);
    auto suformat = formatMemOut(swapUsed);
    memstats.memoryUsed = muformat.value;
    memstats.memUsedFormat = muformat.format;
    memstats.swapUsed = suformat.value;
    memstats.swapUsedFormat = suformat.value;
    return memstats;
}
