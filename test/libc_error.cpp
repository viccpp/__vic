#include<__vic/error.h>
#include<iostream>
#include<exception>
#include<cstring>
#include<cassert>

void run_tests()
{
    __vic::libc_error ex1("My prompt", ERANGE);
    std::cout << ex1.what() << '\n';
    __vic::libc_error ex2(ERANGE);
    std::cout << ex2.what() << '\n';
    __vic::libc_error ex3("Current error");
    std::cout << ex3.what() << '\n';
    __vic::libc_error ex4;
    std::cout << ex4.what() << '\n';
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
