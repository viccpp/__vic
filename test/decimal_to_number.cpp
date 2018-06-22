#include<__vic/str2num.h>
#include<__vic/stdint.h>
#include<stdexcept>
#include<iostream>
#include<cstdio>
#include<limits>
#include<cassert>

template<class TInt>
inline void parse_and_check(
    const char *str, __vic::number_parse_status_t expected_status)
{
    __vic::decimal_parser<TInt> p;
    assert(p.parse(str) == expected_status);
}
void integer_tests()
{
    using __vic::decimal_to_number;
    using __vic::number_parse_status;

    assert(decimal_to_number<int>("4587") == 4587);
    assert(decimal_to_number<long>("-125") == -125L);

    // Integer overflow
    parse_and_check<int8_t>("1000", number_parse_status::unrepresentable);

    // No spaces allowed
    parse_and_check<int>(" 100", number_parse_status::invalid_number);

    // No non-digit chars allowed
    parse_and_check<int>("100a", number_parse_status::invalid_number);

    // No empty strings allowed
    parse_and_check<int>("", number_parse_status::invalid_number);

    parse_and_check<unsigned>("-1", number_parse_status::invalid_number);

    parse_and_check<int>("-", number_parse_status::invalid_number);

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
