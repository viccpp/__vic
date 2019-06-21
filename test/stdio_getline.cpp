#include<__vic/stdio_file.h>
#include<__vic/error.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    __vic::stdio_file file("stdio_getline.cpp", "r");
    if(!file.is_open()) throw __vic::exception("Cannot open file");
    std::string buf;
    buf.reserve(4096);
    while(__vic::getline(file, buf))
        std::cout << buf << '\n';
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
