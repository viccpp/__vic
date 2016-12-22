#include<__vic/error.h>
#include<iostream>
#include<exception>
#include<cstring>
#include<cassert>

void libc_error_tests()
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

void throw_errno_tests()
{
    try
    {
        errno = EDOM;
        __vic::throw_errno("");
        assert(false);
    }
    catch(const __vic::libc_error &ex)
    {
        __vic::libc_error err("");
        assert(ex.code() == errno);
        assert(ex.code() == err.code());
        assert(std::strcmp(ex.what(), err.what()) == 0);
    }
    const int err_no = ERANGE;
    try
    {
        errno = 0;
        __vic::throw_errno("", err_no);
        assert(false);
    }
    catch(const __vic::libc_error &ex)
    {
        __vic::libc_error err("", err_no);
        assert(ex.code() == err_no);
        assert(ex.code() == err.code());
        assert(std::strcmp(ex.what(), err.what()) == 0);
    }
}

void run_tests()
{
    libc_error_tests();
    throw_errno_tests();
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
