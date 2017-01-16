#include<__vic/windows/throw_last_error.h>
#include<__vic/windows/error.h>
#include<windows.h>
#include<iostream>
#include<exception>
#include<cstring>
#include<cassert>

void run_tests()
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
