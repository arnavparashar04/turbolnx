#include <string>
#include <iostream>
#include <iomanip>
#include "turbolnx/ui.h"
#include "turbolnx/memory.h"

void turbolnx::drawoutput(turbolnx::MemoryStatistics memory){
    std::cout << "\033[2J\033[H";
    const std::string RED    = "\033[38;2;224;108;117m";
    const std::string GREEN  = "\033[38;2;152;195;121m";
    const std::string BLUE   = "\033[38;2;97;175;239m";
    const std::string YELLOW = "\033[38;2;229;192;123m";
    const std::string RESET  = "\033[0m";
    std::cout<<std::fixed<<std::setprecision(1);
    std::cout<<BLUE<<"turbolnx\n\n\n"<<RESET;
    std::cout<<RED<<"MEMORY\n\n"<<RESET;

    std::cout<<"Used: "<<memory.memoryUsed<<" "<<memory.memUsedFormat;
    std::cout<<" / "<<memory.totalMemory<<" "<< memory.memTotalFormat<<std::endl; 
    std::cout<<"Cached: "<<memory.memoryCached<<" "<<memory.memCachedFormat<<std::endl;
    std::cout<<"Swap: "<<memory.swapUsed<< " "<<memory.swapUsedFormat;
    std::cout<<" / "<<memory.swapTotal<< " "<<memory.swapTotalFormat<<std::endl;

    std::cout.flush();
}
