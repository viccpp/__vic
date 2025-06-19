#ifndef __VIC_USE_MODULES
#include<__vic/readonly_cstring.h>
#include<iostream>
#include<exception>
#endif
#include<cassert>
#ifdef __VIC_USE_MODULES
import std;
import __vic;
#endif

void run_tests()
{
    static const char cstr[] = "cstring";
    __vic::readonly_cstring st(cstr);
    assert(!st.empty());
    assert(st == cstr);
    assert(compare("a",  st) < 0);

    assert(__vic::readonly_cstring().empty());

    // Check comparison
    assert(st == st);
    assert(!(st != st));
    assert(!(st < st));
    assert(!(st > st));
    assert(st <= st);
    assert(st >= st);

    assert(st == cstr);
    assert(!(st != cstr));
    assert(!(st < cstr));
    assert(!(st > cstr));
    assert(st <= cstr);
    assert(st >= cstr);

    assert(cstr == st);
    assert(!(cstr != st));
    assert(!(cstr < st));
    assert(!(cstr > st));
    assert(cstr <= st);
    assert(cstr >= st);
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
