#ifndef __VIC_USE_MODULES
#include<__vic/ascii_string.h>
#include<iostream>
#include<exception>
#include<cstring>
#include<string>
#endif
#include<cassert>
#ifdef __VIC_USE_MODULES
import std;
import __vic;
#endif

namespace tests {

void tolower_tests()
{
    char st[] = "aBcDe";
    std::string str(st);

    __vic::ascii::tolower(st);
    assert(std::strcmp(st, "abcde") == 0);

    __vic::ascii::tolower(str);
    assert(str == "abcde");
}
void toupper_tests()
{
    char st[] = "aBcDe";
    std::string str(st);

    __vic::ascii::toupper(st);
    assert(std::strcmp(st, "ABCDE") == 0);

    __vic::ascii::toupper(str);
    assert(str == "ABCDE");
}
void run()
{
    tolower_tests();
    toupper_tests();
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
