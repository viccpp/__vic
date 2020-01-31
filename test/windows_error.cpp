#include<__vic/windows/error.h>
#include<__vic/string_utils.h>
#include<windows.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    __vic::windows::error ex1("Out of memory", ERROR_OUTOFMEMORY);
    std::cout << ex1.what() << '\n'; assert(!__vic::ends_with(ex1.what(), " \t\r\n"));
    __vic::windows::error ex2(ERROR_INVALID_FUNCTION);
    std::cout << ex2.what() << '\n'; assert(!__vic::ends_with(ex2.what(), " \t\r\n"));
    __vic::windows::error ex3("Current error");
    std::cout << ex3.what() << '\n'; assert(!__vic::ends_with(ex3.what(), " \t\r\n"));
    __vic::windows::error ex4;
    std::cout << ex4.what() << '\n'; assert(!__vic::ends_with(ex4.what(), " \t\r\n"));
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
