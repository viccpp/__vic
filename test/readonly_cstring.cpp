#include<__vic/readonly_cstring.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    static const char cstr[] = "cstring";
    __vic::readonly_cstring st(cstr);
    assert(!st.empty());
    assert(st == cstr);

    assert(__vic::readonly_cstring().empty());
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
