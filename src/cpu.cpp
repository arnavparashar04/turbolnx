#include "turbolnx/cpu.h"
#include <fstream>
#include <string>
#include <cstdint>
namespace turbolnx {
    
    void initcpustats(CpuStats *cpustats){
       cpustats->idle = 0;
       cpustats->total = 0;
       cpustats->usagePercentage = 0;
    }
    void getCpuStats(CpuStats *prevcpustats){
        std::ifstream cpuinfo("/proc/stat");
        std::string cpunamethrowaway;
        cpuinfo>>cpunamethrowaway;
        uint64_t user, nice, sys, idle, iowait, irq, sirq, steal, guest, guestnice;
        uint64_t total, idlesuper, deltotal, delidle, active;
        cpuinfo>>user>>nice>>sys>>idle>>iowait>>irq>>sirq>>steal>>guest>>guestnice;

        idlesuper = idle + iowait;
        active = user + nice + sys + irq + sirq + steal;
        total = idlesuper + active;
        if(prevcpustats->total != 0&&prevcpustats->idle !=0){
            deltotal = total - prevcpustats->total;
            delidle = idlesuper - prevcpustats->idle;
            prevcpustats->usagePercentage = (static_cast<double>(deltotal - delidle)/deltotal)*100;
            prevcpustats->idle = idlesuper;
            prevcpustats->total = total;
        }
        else {
            prevcpustats->idle = idlesuper;
            prevcpustats->total = total;
        }
    }
}

