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

namespace tests {

bool check_path(const std::string &path)
{
    bool res = __vic::path_exists(path);
    std::cout << path << ' ' << (res ? "exists" : "doesn't exist") << '\n';
    return res;
}
void run()
{
    assert( check_path("."));
    assert( check_path("path_exists.cpp"));
    assert(!check_path("path_doesnt_exist"));
    assert( check_path("../src"));

    assert( __vic::file_exists("path_exists.cpp"));
    assert(!__vic::dir_exists("path_exists.cpp"));
    assert( __vic::dir_exists("."));
    assert(!__vic::file_exists("."));
}

} // namespace

int main()
{
    try
    {
        tests::run();
        return 0;
    }
    catch(const std::exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 1;
}
