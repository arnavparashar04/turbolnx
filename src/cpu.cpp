#include "turbolnx/cpu.h"
#include <fstream>
#include <string>
#include <cstdint>
#include <sys/types.h>
namespace turbolnx {
    
    void initcpustats(CpuStats *cpustats){
       cpustats->idle = 0;
       cpustats->total = 0;
       cpustats->usagePercentage = 0;
       cpustats->temp = 0;
       cpustats->uptimeSeconds = 0;
       cpustats->uptimeMinutes = 0;
       cpustats->uptimeHours = 0;
    }
    void getCpuStats(CpuStats *prevcpustats){

        //gen cpu stats
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
        //temp here onwards
        std::ifstream cpuTemp("/sys/class/thermal/thermal_zone0/temp");
        uint64_t temporary_temperature = 0;
        cpuTemp>>temporary_temperature;
        temporary_temperature = temporary_temperature/1000;
        prevcpustats->temp =temporary_temperature;
        //uptime stuff here onwards
        std::ifstream uptime("/proc/uptime");
        uint64_t totalUptimeS = 0;
        uptime>>totalUptimeS;
        prevcpustats->uptimeHours = totalUptimeS/3600;
        prevcpustats->uptimeMinutes = (totalUptimeS%3600) / 60;
        prevcpustats->uptimeSeconds = totalUptimeS &60;


    }
}

