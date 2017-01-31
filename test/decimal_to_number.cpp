#include<__vic/str2num.h>
#include<__vic/stdint.h>
#include<stdexcept>
#include<iostream>
#include<cstdio>
#include<limits>
#include<cassert>

void integer_tests()
{
    using __vic::decimal_to_number;

    assert(decimal_to_number<int>("4587") == 4587);
    assert(decimal_to_number<long>("-125") == -125L);

    try
    {
        // Integer overflow
        decimal_to_number<int8_t>("1000");
        assert(false);
    }
    catch(const std::range_error & ) {}

    try
    {
        // No spaces allowed
        decimal_to_number<int>(" 100");
        assert(false);
    }
    catch(const std::invalid_argument & ) {}

    try
    {
        // No non-digit chars allowed
        decimal_to_number<int>("100a");
        assert(false);
    }
    catch(const std::invalid_argument & ) {}

    try
    {
        // No empty strings allowed
        decimal_to_number<int>("");
        assert(false);
    }
    catch(const std::invalid_argument & ) {}

    try
    {
        std::cout << decimal_to_number<unsigned>("-1") << std::endl;
        assert(false);
    }
    catch(const std::invalid_argument & ) {}

    __VIC_LONGLONG n;
    decimal_to_number(std::string("10000"), n);
    assert(n == 10000);

    int min_int = std::numeric_limits<int>::min();
    char buf[64];
    std::sprintf(buf, "%d", min_int);
    decimal_to_number(buf, min_int);
    assert(min_int == std::numeric_limits<int>::min());
}
void run_tests()
{
    integer_tests();
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
