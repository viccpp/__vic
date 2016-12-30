#include<__vic/date_time.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    using __vic::is_leap_year;
    assert( is_leap_year(1996));
    assert(!is_leap_year(1997));
    assert( is_leap_year(1600));
    assert(!is_leap_year(1700));
    assert(!is_leap_year(1800));
    assert(!is_leap_year(1900));
    assert( is_leap_year(2000));
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
