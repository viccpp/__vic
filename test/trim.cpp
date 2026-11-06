#ifndef __VIC_USE_MODULES
#include<__vic/string_utils.h>
#include<__vic/ascii.h>
#include<iostream>
#include<exception>
#include<cstring>
#endif
#include<cassert>
#ifdef __VIC_USE_MODULES
#include<version>
import std;
import __vic;
#endif

namespace tests {

using namespace __vic;
using __vic::ascii::isspace;

char first(const char *s)
{
    assert(s && *s != '\0');
    return *s;
}
char first(
#if __cpp_lib_string_view
    std::string_view
#else
    const std::string &
#endif
        s)
{
    assert(!s.empty());
    return s[0];
}
char last(const char *st)
{
    assert(st && *st != '\0');
    return *(std::strchr(st, '\0') - 1);
}
char last(
#if __cpp_lib_string_view
    std::string_view
#else
    const std::string &
#endif
        st)
{
    assert(!st.empty());
    return *(st.end() - 1);
}
/*char last(const string_ref &st)
{
    assert(!st.empty());
    return *(st.end() - 1);
}*/
bool in_set(char ch, const char *set)
{
    assert(set);
    return std::strchr(set, ch);
}
// Test internal utilities
void test_utils()
{
    assert(first("123") == '1');
    assert(first(std::string("123")) == '1');
    assert(last("123") == '3');
    assert(last(std::string("123")) == '3');
    //assert(last(string_ref("123")) == '3');
    assert(!in_set('z', "abc"));
    assert(in_set('a', "abc"));
    assert(in_set('b', "abc"));
    assert(in_set('c', "abc"));
}

void trim_default_test(const char *src)
{
    assert(src);
    std::cout << "Default trim. Source: |" << src << "|\n";
    {
        char s[32];
        assert(std::strlen(src) < sizeof s);

        std::strcpy(s, src);
        std::cout << trim(s) << "|\n";
        assert(!isspace(first(s)));
        assert(!isspace(last(s)));

        std::strcpy(s, src);
        std::cout << trim_front(s) << "|\n";
        assert(!isspace(first(s)));

        std::strcpy(s, src);
        std::cout << trim_back(s) << "|\n";
        assert(!isspace(last(s)));
    }
    {
        std::string s;

        s = src;
        std::cout << trim(s) << "|\n";
        assert(!isspace(first(s)));
        assert(!isspace(last(s)));

        s = src;
        std::cout << trim_front(s) << "|\n";
        assert(!isspace(first(s)));

        s = src;
        std::cout << trim_back(s) << "|\n";
        assert(!isspace(last(s)));
    }
#if __cpp_lib_string_view
    {
        std::string_view s;

        s = src;
        std::cout << trim(s) << "|\n";
        assert(!isspace(first(s)));
        assert(!isspace(last(s)));

        s = src;
        std::cout << trim_front(s) << "|\n";
        assert(!isspace(first(s)));

        s = src;
        std::cout << trim_back(s) << "|\n";
        assert(!isspace(last(s)));
    }
#endif
}
void trim_char_test(const char *src, char ch)
{
    assert(src);
    std::cout << "Trim char. Source: |" << src << "|\n";
    {
        char s[32];
        assert(std::strlen(src) < sizeof s);

        std::strcpy(s, src);
        std::cout << trim(s, ch) << "|\n";
        assert(first(s) != ch);
        assert(last(s) != ch);

        std::strcpy(s, src);
        std::cout << trim_front(s, ch) << "|\n";
        assert(first(s) != ch);

        std::strcpy(s, src);
        std::cout << trim_back(s, ch) << "|\n";
        assert(last(s) != ch);
    }
    {
        std::string s;

        s = src;
        std::cout << trim(s, ch) << "|\n";
        assert(first(s) != ch);
        assert(last(s) != ch);

        s = src;
        std::cout << trim_front(s, ch) << "|\n";
        assert(first(s) != ch);

        s = src;
        std::cout << trim_back(s, ch) << "|\n";
        assert(last(s) != ch);
    }
#if __cpp_lib_string_view
    {
        std::string_view s;

        s = src;
        std::cout << trim(s, ch) << "|\n";
        assert(first(s) != ch);
        assert(last(s) != ch);

        s = src;
        std::cout << trim_front(s, ch) << "|\n";
        assert(first(s) != ch);

        s = src;
        std::cout << trim_back(s, ch) << "|\n";
        assert(last(s) != ch);
    }
#endif
}
void trim_set_test(const char *src, const char *set)
{
    assert(src);
    std::cout << "Trim set. Source: |" << src << "|\n";
    {
        char s[32];
        assert(std::strlen(src) < sizeof s);

        std::strcpy(s, src);
        std::cout << trim(s, set) << "|\n";
        assert(!in_set(first(s), set));
        assert(!in_set(last(s), set));

        std::strcpy(s, src);
        std::cout << trim_front(s, set) << "|\n";
        assert(!in_set(first(s), set));

        std::strcpy(s, src);
        std::cout << trim_back(s, set) << "|\n";
        assert(!in_set(last(s), set));
    }
    {
        std::string s;

        s = src;
        std::cout << trim(s, set) << "|\n";
        assert(!in_set(first(s), set));
        assert(!in_set(last(s), set));

        s = src;
        std::cout << trim_front(s, set) << "|\n";
        assert(!in_set(first(s), set));

        s = src;
        std::cout << trim_back(s, set) << "|\n";
        assert(!in_set(last(s), set));
    }
#if __cpp_lib_string_view
    {
        std::string_view s;

        s = src;
        std::cout << trim(s, set) << "|\n";
        assert(!in_set(first(s), set));
        assert(!in_set(last(s), set));

        s = src;
        std::cout << trim_front(s, set) << "|\n";
        assert(!in_set(first(s), set));

        s = src;
        std::cout << trim_back(s, set) << "|\n";
        assert(!in_set(last(s), set));
    }
#endif
}
void trimmed_default_test(const char *src)
{
    assert(src);
    std::cout << "Default trimmed. Source: |" << src << "|\n";
#if __cpp_lib_string_view
    std::string_view
#else
    std::string
#endif
        st;

    st = trimmed(src);
    assert(!isspace(first(st)));
    assert(!isspace(last(st)));
    std::cout << st << "|\n";

    st = trimmed_front(src);
    assert(!isspace(first(st)));
    std::cout << st << "|\n";

    st = trimmed_back(src);
    assert(!isspace(last(st)));
    std::cout << st << "|\n";
}
void trimmed_char_test(const char *src, char ch)
{
    assert(src);
    std::cout << "Trimmed char. Source: |" << src << "|\n";
#if __cpp_lib_string_view
    std::string_view
#else
    std::string
#endif
        st;

    st = trimmed(src, ch);
    assert(first(st) != ch);
    assert(last(st) != ch);
    std::cout << st << "|\n";

    st = trimmed_front(src, ch);
    assert(first(st) != ch);
    std::cout << st << "|\n";

    st = trimmed_back(src, ch);
    assert(last(st) != ch);
    std::cout << st << "|\n";
}
void trimmed_set_test(const char *src, const char *set)
{
    assert(src);
    std::cout << "Trimmed set. Source: |" << src << "|\n";
#if __cpp_lib_string_view
    std::string_view
#else
    std::string
#endif
        st;

    st = trimmed(src, set);
    assert(!in_set(first(st), set));
    assert(!in_set(last(st), set));
    std::cout << st << "|\n";

    st = trimmed_front(src, set);
    assert(!in_set(first(st), set));
    std::cout << st << "|\n";

    st = trimmed_back(src, set);
    assert(!in_set(last(st), set));
    std::cout << st << "|\n";
}
void run()
{
    test_utils();

    trim_default_test(" \tabc  \t  ");
    std::cout << std::endl;
    trim_char_test("  abc   ", ' ');
    std::cout << std::endl;
    trim_set_test(" \tabc  \t  ", " \t\r\n\f");
    std::cout << std::endl;

    trimmed_default_test(" \tabc  \t  ");
    std::cout << std::endl;
    trimmed_char_test("  abc   ", ' ');
    std::cout << std::endl;
    trimmed_set_test(" \tabc  \t  ", " \t\r\n\f");
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
