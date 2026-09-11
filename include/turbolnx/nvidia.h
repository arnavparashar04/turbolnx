#pragma once
#include <nvml.h>
#include <cstdint>
#include <sys/types.h>
#include <string>
namespace turbolnx {
   struct nvidiaStats{
       unsigned int temp;
       unsigned int usage;
       unsigned int power;
       uint64_t vramUsed;
       uint64_t vramTotal;
       std::string name;
   };

   nvidiaStats getNvidiaStats();
}
