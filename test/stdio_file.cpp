#ifndef __VIC_USE_MODULES
#include<__vic/stdio_file.h>
#include<__vic/error.h>
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
    __vic::stdio_file file("stdio_file.cpp", "r");
    if(!file.is_open()) throw __vic::exception("Cannot open file");
    std::fgetc(file);
    file.close();
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
