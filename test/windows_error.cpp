#include<__vic/windows/error.h>
#include<windows.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    __vic::windows::error ex1("Out of memory", ERROR_OUTOFMEMORY);
    std::cout << ex1.what() << '\n';
    __vic::windows::error ex2(ERROR_INVALID_FUNCTION);
    std::cout << ex2.what() << '\n';
    __vic::windows::error ex3("Current error");
    std::cout << ex3.what() << '\n';
    __vic::windows::error ex4;
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
