#include "turbolnx/nvidia.h"
#include <nvml.h>

namespace turbolnx {
    nvidiaStats getNvidiaStats(){
        
       
        nvidiaStats stats{};
        nvmlDevice_t device;
        nvmlDeviceGetHandleByIndex(0, &device);
        
        char name[NVML_DEVICE_NAME_V2_BUFFER_SIZE];
        nvmlDeviceGetName(device, name, sizeof(name));
        stats.name = name;

        nvmlUtilization_t utilization;
        nvmlDeviceGetUtilizationRates(device, &utilization);
        stats.usage = utilization.gpu;
        
        nvmlTemperature_t temperature;
        temperature.version = nvmlTemperature_v1;
        temperature.sensorType = NVML_TEMPERATURE_GPU;
        nvmlDeviceGetTemperatureV(device, &temperature); 
        stats.temp = temperature.temperature;

        nvmlMemory_t memory;
        nvmlDeviceGetMemoryInfo(device, &memory);
        stats.vramTotal = memory.total;
        stats.vramUsed = memory.used;

        unsigned int power;
        nvmlDeviceGetPowerUsage(device, &power);
        stats.power = power / 1000;

        
        return stats;
    }
}
