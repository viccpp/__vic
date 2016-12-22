#include<__vic/defs.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    int m[] = {1, 2, 3};
    assert(__vic::array_size(m) == sizeof m / sizeof *m);
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
