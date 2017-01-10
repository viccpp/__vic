#include<__vic/windows/error.h>
#include<windows.h>
#include<iostream>
#include<exception>
#include<cstring>
#include<cassert>

void windows_error_tests()
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

void throw_last_error_tests()
{
    try
    {
        ::SetLastError(ERROR_ACCESS_DENIED);
        assert(::GetLastError() == ERROR_ACCESS_DENIED);
        __vic::windows::throw_last_error("");
        assert(false);
    }
    catch(const __vic::windows::error &ex)
    {
        __vic::windows::error err("", ex.code());
        assert(err.code() == ERROR_ACCESS_DENIED);
        assert(std::strcmp(ex.what(), err.what()) == 0);
    }
    const DWORD err_code = ERROR_INVALID_HANDLE;
    try
    {
        ::SetLastError(ERROR_SUCCESS);
        __vic::windows::throw_last_error("", err_code);
        assert(false);
    }
    catch(const __vic::windows::error &ex)
    {
        __vic::windows::error err("", err_code);
        assert(ex.code() == err_code);
        assert(ex.code() == err.code());
        assert(std::strcmp(ex.what(), err.what()) == 0);
    }
}

void run_tests()
{
    windows_error_tests();
    throw_last_error_tests();
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
