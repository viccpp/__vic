#ifndef __VIC_USE_MODULES
#include<__vic/defs.h>
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
    int m[] = {1, 2, 3};
    assert(__vic::array_size(m) == sizeof m / sizeof *m);
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
