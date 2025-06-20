#ifndef __VIC_USE_MODULES
#include<__vic/posix/file_stat.h>
#include<iostream>
#include<exception>
#endif
#include<cassert>
#include<sys/stat.h>
#ifdef __VIC_USE_MODULES
import std;
import __vic;
#endif

void run_tests()
{
    __vic::posix::file_stat s;

    assert(s.get_if_exists("posix_file_stat.cpp") == true);
    s.get("posix_file_stat.cpp");
    assert(s.is_regular());

    assert(s.get_if_exists("posix_file_stat.doesnotexist") == false);
    try {
        s.get("posix_file_stat.doesnotexist");
        assert(false);
    } catch(const std::exception &) {
        // OK
    }

    struct ::stat ss = s;
    s = ss;
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
