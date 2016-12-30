#include<__vic/date_time.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    assert(__vic::days_between_years(0,0) == 0);
    assert(!__vic::is_leap_year(2003));
    assert(__vic::days_between_years(2003, 2004) == 365);
    assert(__vic::days_between_years(2004, 2003) == -365);
    assert(__vic::is_leap_year(2012));
    assert(__vic::days_between_years(2012, 2013) == 366);
    assert(!__vic::is_leap_year(2013));
    assert(__vic::days_between_years(2012, 2014) == 366 + 365);
    assert(__vic::days_between_years(2012, 2019) == 365 * 7 + 2);
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
