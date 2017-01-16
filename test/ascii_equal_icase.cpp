#include<__vic/ascii_string.h>
#include<iostream>
#include<exception>
#include<string>
#include<cassert>

void run_tests()
{
    using __vic::ascii::equal_icase;

    assert(equal_icase("abc", "abc"));
    assert(equal_icase("aBc", "AbC"));
    assert(!equal_icase("abc", "ab"));
    assert(!equal_icase("abc", "abd"));

    assert(equal_icase(std::string("abc"), std::string("abc")));
    assert(equal_icase(std::string("aBc"), std::string("AbC")));
    assert(!equal_icase(std::string("abc"), std::string("ab")));
    assert(!equal_icase(std::string("abc"), std::string("abd")));
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
