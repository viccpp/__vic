#include<__vic/stdint.h>
#include<iostream>
#include<exception>
#include<cassert>

void run_tests()
{
    assert(sizeof(int8_t)  == 1);
    assert(sizeof(int16_t) == 2);
    assert(sizeof(int32_t) == 4);
    assert(sizeof(int64_t) == 8);

    assert(sizeof(uint8_t)  == 1);
    assert(sizeof(uint16_t) == 2);
    assert(sizeof(uint32_t) == 4);
    assert(sizeof(uint64_t) == 8);

    assert(sizeof(int_least8_t)  >= 1);
    assert(sizeof(int_least16_t) >= 2);
    assert(sizeof(int_least32_t) >= 4);
    assert(sizeof(int_least64_t) >= 8);

    assert(sizeof(uint_least8_t)  >= 1);
    assert(sizeof(uint_least16_t) >= 2);
    assert(sizeof(uint_least32_t) >= 4);
    assert(sizeof(uint_least64_t) >= 8);

    assert(sizeof(int_fast8_t)  >= 1);
    assert(sizeof(int_fast16_t) >= 2);
    assert(sizeof(int_fast32_t) >= 4);
    assert(sizeof(int_fast64_t) >= 8);

    assert(sizeof(uint_fast8_t)  >= 1);
    assert(sizeof(uint_fast16_t) >= 2);
    assert(sizeof(uint_fast32_t) >= 4);
    assert(sizeof(uint_fast64_t) >= 8);

    (void) intmax_t(0);
    (void)uintmax_t(0);

    (void) intptr_t(0);
    (void)uintptr_t(0);

    assert(sizeof(__vic::int_exactly_bytes<1>::type) == 1);
    assert(sizeof(__vic::int_exactly_bytes<2>::type) == 2);
    assert(sizeof(__vic::int_exactly_bytes<4>::type) == 4);
    assert(sizeof(__vic::int_exactly_bytes<8>::type) == 8);

    assert(sizeof(__vic::uint_exactly_bytes<1>::type) == 1);
    assert(sizeof(__vic::uint_exactly_bytes<2>::type) == 2);
    assert(sizeof(__vic::uint_exactly_bytes<4>::type) == 4);
    assert(sizeof(__vic::uint_exactly_bytes<8>::type) == 8);
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
