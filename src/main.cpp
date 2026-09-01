#include "turbolnx/memory.h"
#include "turbolnx/ui.h"
#include <thread>
#include <chrono>

int main(int argc, char *argv[]){
    while(1){
        auto memory = turbolnx::getMemoryStatistics();
        turbolnx::drawoutput(memory); 
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
