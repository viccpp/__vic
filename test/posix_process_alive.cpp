#ifndef __VIC_USE_MODULES
#include<__vic/posix/process.h>
#include<iostream>
#include<exception>
#endif
#include<cassert>
#include<unistd.h>
#ifdef __VIC_USE_MODULES
import std;
import __vic;
#endif

void run_tests()
{
    assert(__vic::posix::process_alive(::getpid()));
    assert(__vic::posix::process_alive(1));
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
