#ifndef __VIC_USE_MODULES
#include<__vic/windows/critical_section.h>
#include<iostream>
#include<exception>
#endif
#ifdef __VIC_USE_MODULES
#include<__vic/modules/windows.h>
import std;
import __vic;
#endif

void native_test()
{
    CRITICAL_SECTION cs;
    ::InitializeCriticalSection(&cs);
    __vic::windows::CSGuard guard(cs);
}
void wrapper_test()
{
    __vic::windows::CriticalSection cs;
    __vic::windows::CSGuard guard(cs);
}
void run_tests()
{
    native_test();
    wrapper_test();
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
