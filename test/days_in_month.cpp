#include<__vic/date_time.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    using __vic::days_in_month;
    assert(days_in_month(1,  0) == 31);
    assert(days_in_month(2,  1997) == 28);
    assert(days_in_month(2,  1996) == 29);
    assert(days_in_month(3,  0) == 31);
    assert(days_in_month(4,  0) == 30);
    assert(days_in_month(5,  0) == 31);
    assert(days_in_month(6,  0) == 30);
    assert(days_in_month(7,  0) == 31);
    assert(days_in_month(8,  0) == 31);
    assert(days_in_month(9,  0) == 30);
    assert(days_in_month(10, 0) == 31);
    assert(days_in_month(11, 0) == 30);
    assert(days_in_month(12, 0) == 31);
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
