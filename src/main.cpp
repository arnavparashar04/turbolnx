#include "turbolnx/cpu.h"
#include "turbolnx/memory.h"
#include "turbolnx/nvidia.h"
#include "turbolnx/ui.h"
#include <thread>
#include <chrono>
#include <nvml.h>

int main(int argc, char *argv[]){
    turbolnx::CpuStats stats;
    turbolnx::initcpustats(&stats);
    nvmlInit();

    while(1){
        auto memory = turbolnx::getMemoryStatistics();
        auto nvidia = turbolnx::getNvidiaStats();
        turbolnx::getCpuStats(&stats);
        turbolnx::drawoutput(memory, stats, nvidia);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    nvmlShutdown();
}
