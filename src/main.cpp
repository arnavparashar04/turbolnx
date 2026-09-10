#include "turbolnx/cpu.h"
#include "turbolnx/memory.h"
#include "turbolnx/ui.h"
#include <thread>
#include <chrono>

int main(int argc, char *argv[]){
    turbolnx::CpuStats stats;
    turbolnx::initcpustats(&stats);
    while(1){
        auto memory = turbolnx::getMemoryStatistics();
        turbolnx::getCpuStats(&stats);
        turbolnx::drawoutput(memory, stats); 
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
