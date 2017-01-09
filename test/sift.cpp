#include<__vic/string_ops.h>
#include<iostream>
#include<exception>
#include<cassert>
#include<cstring>

void run_tests()
{
    char st[] = "..ab.c..d.e.";
    std::string str(st);

    __vic::sift(st, ".");
    assert(!std::strcmp(st, "abcde"));
    std::cout << st << '\n';
    __vic::sift(str, ".");
    assert(str == "abcde");
    std::cout << str << '\n';
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
