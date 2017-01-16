#define __VIC_DEFINE_OSTREAM_INSERTERS 1
#include<__vic/string_ref.h>
#include<iostream>
#include<exception>
#include<cassert>

namespace tests {

void print(__vic::string_ref s)
{
    std::cout << s << '\n';
}

void run()
{
    print("String literal");
    print(std::string("std::string"));

    const char str[] = "str";
    __vic::string_ref sr = str;

    assert(sr == str);
    assert(!(sr != str));
    assert(sr > "abc");
    assert(sr > "st");
    assert(sr < "z");
    assert(sr >= str);
    assert(sr >= "abc");

    // Check assignment
    sr = str;
    assert(sr == str);
    std::string std_str(str);
    sr = std_str;
    assert(sr == std_str);
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
