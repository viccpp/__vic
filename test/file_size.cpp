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
    std::cout << "File size is " <<
        __vic::file_size("file_size.cpp") << " bytes\n";
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
