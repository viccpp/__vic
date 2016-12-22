#include<__vic/posix/file.h>
#include<__vic/error.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    __vic::posix::file file("posix_file.cpp", O_RDONLY);
    if(!file.is_open()) throw __vic::libc_error("Cannot open file");
    char buf[256];
    size_t n = file.read_max(buf, sizeof buf);
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
