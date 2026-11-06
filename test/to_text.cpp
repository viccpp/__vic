#ifndef __VIC_USE_MODULES
#include<__vic/to_text.h>
#include<iostream>
#include<exception>
#include<cstdio>
#include<limits>
#endif
#include<cassert>
#ifdef __VIC_USE_MODULES
import std;
import __vic;
#endif

namespace tests {

template<class T>
std::string to_text(const T &v)
{
    std::string s;
    __vic::to_text_append(v, s);
    return s;
}

void test_char()
{
    assert(to_text('A') == "A");
}
void test_string()
{
    const std::string s("abc");
    assert(to_text(s) == s);
}
void test_string_view()
{
#if __cpp_lib_string_view
    const std::string_view s("abc");
    assert(to_text(s) == s);
#endif
}
void test_bool()
{
    assert(to_text(true)  == "1");
    assert(to_text(false) == "0");
}
void test_unsigned_integers()
{
    const unsigned n = 123;
    const std::string res("123");

    assert(to_text(static_cast<unsigned char>(n)) == res);
    assert(to_text(static_cast<unsigned short>(n)) == res);
    assert(to_text(static_cast<unsigned>(n)) == res);
    assert(to_text(static_cast<unsigned long>(n)) == res);
    assert(to_text(static_cast<unsigned long long>(n)) == res);
}
void test_signed_integers()
{
    const int n = -123;
    const std::string res("-123");

    assert(to_text(static_cast<signed char>(n)) == res);
    assert(to_text(static_cast<short>(n)) == res);
    assert(to_text(static_cast<int>(n)) == res);
    assert(to_text(static_cast<long>(n)) == res);
    assert(to_text(static_cast<long long>(n)) == res);
}
void test_floats()
{
    const double n = 123;
    const std::string res("123");

    assert(to_text(static_cast<float>(n)) == res);
    assert(to_text(static_cast<double>(n)) == res);
    assert(to_text(static_cast<long double>(n)) == res);

    assert(to_text(std::numeric_limits<double>::quiet_NaN()) == "NAN");
    assert(to_text(std::numeric_limits<double>::infinity()) == "INF");
}
void test_pointer()
{
    const void *p = 0;
    assert(!to_text(p).empty());
}
void run()
{
    std::string st;
    __vic::to_text_append(123, st);
    assert(st == "123");
    __vic::to_text_append(45UL, st);
    assert(st == "12345");
    st.clear();
    __vic::to_text_append(-123, st);
    assert(st == "-123");
    st.clear();
    {
        const int min_int = std::numeric_limits<int>::min();
        __vic::to_text_append(min_int, st);
        char buf[64];
        assert(st.length() < sizeof buf);
        std::sprintf(buf, "%d", min_int);
        assert(st == buf);
    }
    st.clear();
    __vic::to_text_append(1.2, st);
    __vic::to_text_append(true, st);
    __vic::to_text_append(short(1), st);
    __vic::to_text_append(&st, st);

    test_char();
    test_string();
    test_string_view();
    test_bool();
    test_unsigned_integers();
    test_signed_integers();
    test_floats();
    test_pointer();
}

} // namespace

int main()
{
    try
    {
        tests::run();
        return 0;
    }
    catch(const std::exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 1;
}
