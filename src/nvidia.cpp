#include "turbolnx/nvidia.h"
#include <nvml.h>

namespace turbolnx {

    struct formattedValue1{
        double value;
        std::string format;
    };

    formattedValue1 formatMemOut1(uint64_t inputval){
       if (inputval<1024ULL) {
           return formattedValue1{.value = static_cast<double>(inputval),.format = "B"};
       }
       else if (inputval < 1024ULL*1024) {
           return formattedValue1{.value = static_cast<double>(inputval/1024.0),.format = "KiB"}; 
       }
       else if (inputval < 1024ULL*1024*1024) {
           return formattedValue1{.value = static_cast<double>(inputval/(1024.0*1024.0)),.format = "MiB"};
       }
       else if(inputval<1024ULL*1024*1024*1024){
           return formattedValue1{.value = static_cast<double>(inputval)/(1024.0*1024.0*1024.0),.format = "GiB"};
       }
       else {
            return formattedValue1{.value = static_cast<double>(inputval)/(1024.0*1024.0*1024.0*1024.0),.format = "TiB"};
       }
    }
    

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
        auto formatVTotal = formatMemOut1(memory.total);
        stats.vramTotal = formatVTotal.value;
        stats.vramTotalFormat = formatVTotal.format;
        auto formatVUsed = formatMemOut1(memory.used);
        stats.vramUsed = formatVUsed.value;
        stats.vramUsedFormat = formatVUsed.format;

        unsigned int power;
        nvmlDeviceGetPowerUsage(device, &power);
        stats.power = power / 1000;

        
        return stats;
    }
}
