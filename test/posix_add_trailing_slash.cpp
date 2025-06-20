#ifndef __VIC_USE_MODULES
#include<__vic/posix/fs.h>
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
    std::string path("/a/b");
    __vic::posix::add_trailing_slash(path);
    assert(*path.rbegin() == '/');

    assert(__vic::posix::with_trailing_slash("/a")  == "/a/");
    assert(__vic::posix::with_trailing_slash("/a/") == "/a/");
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
