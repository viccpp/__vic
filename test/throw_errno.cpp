#include<__vic/throw_errno.h>
#include<__vic/error.h>
#include<iostream>
#include<exception>
#include<cstring>
#include<cassert>

void run_tests()
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
