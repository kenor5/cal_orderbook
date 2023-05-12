#include "include/getbasic.h"
#include "include/calculate.h"
#include <ctime>

// cd src and make and in kernel run ./csob
// there is a breakpoint in getbasic.cpp to show tjhe documents
int main(int argc, char* argv[])
{
    // std::cout << "Hello World!" << std::endl;
    if(argc!=2)
    {
        std::cerr<<"provide arg num: " << argc << "\n[usage]: ./csob dirname\n";
        return 0;
    }

    std::string name= argv[1];

    clock_t start, end;
    
    start = clock();
    // GetBasic getbasic("../../../Data/data/20221012");
    GetBasic getbasic(name);
    end = clock();
    std::cout << "load: " << (double)(end-start)/CLOCKS_PER_SEC << "s" << std::endl;

    auto orders = getbasic.get_Orders();
    auto trades = getbasic.get_Trades();

        start = clock();
        calculator cal;
        cal.do_calculation(orders, trades);
        end = clock();
    std::cout << "cal: " << (double)(end-start)/CLOCKS_PER_SEC << "s" << std::endl;
    
    return 0;
}