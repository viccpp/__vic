#ifndef __VIC_USE_MODULES
#include<__vic/string_buffer.h>
#include<iostream>
#include<exception>
#include<cstddef>
#endif
#include<cassert>
#ifdef __VIC_USE_MODULES
#include<version>
import std;
import __vic;
#endif

void test_basic_inserters()
{
    __vic::string_buffer s;
    s << char();
    s << "";
#if __cpp_lib_string_view
    s << std::string_view{};
#endif
    s << std::string();
    s << __vic::string_buffer();

    typedef signed char schar;
    typedef signed char uchar;
    typedef unsigned short ushort;
    typedef unsigned long ulong;
    typedef long long llong;
    typedef unsigned long long ullong;

    s << schar();
    s << short();
    s << int();
    s << long();
    s << llong();

    s << uchar();
    s << ushort();
    s << unsigned();
    s << ulong();
    s << ullong();

    typedef long double ldouble;

    s << float();
    s << double();
    s << ldouble();

    const void *ptr = 0;
    s << ptr;
}

void run_tests()
{
    const std::size_t initial_capacity = 64;
    __vic::string_buffer s(initial_capacity);
    assert(s.empty());
    assert(s.capacity() >= initial_capacity);

    s << 1;
    assert(s == "1");
    s << ' ' << 2.0 << " " << true;
    std::string std_str = s;
    s = std_str;
    const char *c_str = s;
    s.clear() << static_cast<const void *>(c_str);

    test_basic_inserters();
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
