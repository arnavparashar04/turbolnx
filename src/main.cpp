#include <iostream>
#include "turbolnx/memory.h"

int main(int argc, char *argv[]){
    auto memory = turbolnx::getMemoryStatistics();
    std::cout << "Total: "<< memory.totalMemory << ' '<< memory.memTotalFormat << '\n';
    std::cout << "Used: "<< memory.memoryUsed << ' '<< memory.memUsedFormat << '\n';
}
