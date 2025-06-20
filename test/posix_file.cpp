#ifndef __VIC_USE_MODULES
#include<__vic/posix/file.h>
#include<__vic/error.h>
#include<iostream>
#include<exception>
#include<cstddef>
#endif
#include<cassert>
#ifdef __VIC_USE_MODULES
import std;
import __vic;
#endif

void run_tests()
{
    __vic::posix::file file("posix_file.cpp", O_RDONLY);
    if(!file.is_open()) throw __vic::libc_error("Cannot open file");
    char buf[256];
    std::size_t n = file.read_max(buf, sizeof buf);
    assert(n > 0);
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
