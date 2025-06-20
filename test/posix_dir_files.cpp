#ifndef __VIC_USE_MODULES
#include<__vic/posix/dir_files.h>
#include<iostream>
#include<exception>
#endif
#include<cassert>
#ifdef __VIC_USE_MODULES
import std;
import __vic;
#endif

namespace tests {

void print(__vic::posix::dir_files &files)
{
    assert(files.is_open());
    while(const char *f = files.next())
        std::cout << f << '\n';
}
void run()
{
    std::cout << "All files:\n";
    __vic::posix::dir_files files(".");
    print(files);

    std::cout << "\n*.cpp files:\n";
    __vic::posix::dir_files cpp_files(".", "*.cpp");
    print(cpp_files);
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
