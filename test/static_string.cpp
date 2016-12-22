#include<__vic/static_string.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    static const char cstr[] = "static_string";
    __vic::static_string st(cstr);
    assert(!st.empty());
    assert(st == cstr);

    assert(__vic::static_string().empty());
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
