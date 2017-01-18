#include<__vic/fs.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    std::cout << "File size is " <<
        __vic::file_size("file_size.cpp") << " bytes\n";
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
