#ifndef __VIC_USE_MODULES
#include<__vic/fs.h>
#include<iostream>
#include<exception>
#endif
#include<cassert>
#ifdef __VIC_USE_MODULES
import std;
import __vic;
#endif

void run_tests()
{
    std::cout << "Current dir is " << __vic::get_current_dir() << '\n';
}

int main()
{
    try
    {
        run_tests();
        return 0;
    }
    catch(const std::exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 1;
}
