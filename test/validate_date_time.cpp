#include<__vic/date_time.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    __vic::validate_date(2016, 12, 31);
    __vic::validate_time(11, 32, 15);
    __vic::validate_time(0, 0, 0);
    assert(__vic::is_leap_year(2016));
    __vic::validate_date_time(2016, 2, 29, 12, 0, 0);
    try
    {
        __vic::validate_date(0, 1, 1);
        assert(false); // NOTREACHED
    }
    catch(__vic::invalid_date) {} // OK
    try
    {
        __vic::validate_date(1, 0, 1);
        assert(false); // NOTREACHED
    }
    catch(__vic::invalid_date) {} // OK
    try
    {
        __vic::validate_date(1, 13, 1);
        assert(false); // NOTREACHED
    }
    catch(__vic::invalid_date) {} // OK
    try
    {
        assert(!__vic::is_leap_year(2015));
        __vic::validate_date(2015, 2, 29);
        assert(false); // NOTREACHED
    }
    catch(__vic::invalid_date) {} // OK
    try
    {
        __vic::validate_time(25, 0, 0);
        assert(false); // NOTREACHED
    }
    catch(__vic::invalid_date) {} // OK
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
