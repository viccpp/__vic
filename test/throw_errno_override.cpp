#include<__vic/throw_errno.h>
#include<__vic/error.h>
#include<iostream>
#include<exception>
#include<cstring>
#include<cassert>

//////////////////////////////////////////////////////////////////////////////
struct my_exception : public __vic::exception
{
    explicit my_exception(const char *msg) : __vic::exception(msg) {}
};
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// Override library functions to throw my_exception
//----------------------------------------------------------------------------
void __vic::throw_errno(const char *prompt, int err_no)
{
    throw my_exception(prompt);
}
//----------------------------------------------------------------------------

void run_tests()
{
    try
    {
        __vic::throw_errno("test");
        assert(false);
    }
    catch(const my_exception & )
    {
        // OK
    }
    catch(...)
    {
        assert(false);
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
