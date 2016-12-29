#include<__vic/bits.h>
#include<iostream>
#include<exception>
#include<cassert>

namespace tests {

void nibble_tests()
{
    char ch = '\xFA';
    std::cout << std::hex << std::uppercase <<
        __vic::hi_nibble(ch) << ' ' << __vic::lo_nibble(ch) << '\n';
    assert(__vic::hi_nibble(ch) == 0xF);
    assert(__vic::lo_nibble(ch) == 0xA);
}
void ones_test()
{
    std::cout << __vic::lsb_ones<int>(5) << '\n';
    assert(__vic::lsb_ones<int>(5) == 0x1F);
    std::cout << unsigned(__vic::msb_ones<uint8_t>(5)) << '\n';
    assert(__vic::msb_ones<uint8_t>(5) == uint8_t('\xF8'));
}
void get_lsbs_test()
{
    std::cout << __vic::get_lsbs(~int(0), 6) << '\n';
    assert(__vic::get_lsbs(~int(0), 6) == 0x3F);
}
void ord_test()
{
    char ch = -20;
    std::cout << std::dec << __vic::ord(ch) << '\n';
    assert(__vic::ord(ch) == 236);
}
void to_hex_digit_tests()
{
    assert(__vic::to_hex_digit_upper(1) == '1');
    assert(__vic::to_hex_digit_lower(1) == '1');
    assert(__vic::to_hex_digit_upper(10) == 'A');
    assert(__vic::to_hex_digit_lower(10) == 'a');
}
void hex_to_number_test()
{
    for(int i = 0; i < 256; i++)
        std::cout << __vic::hex_to_number(i) << ' ';
    std::cout << '\n';
}
void swap_nibbles_test()
{
    assert(__vic::swapped_nibbles(0x12) == 0x21);
}
void rot_tests()
{
    assert(__vic::rotl(uint32_t(0x12345678), 8) == uint32_t(0x34567812));
    assert(__vic::rotr(uint32_t(0x12345678), 8) == uint32_t(0x78123456));
}
void run()
{
    nibble_tests();
    ones_test();
    get_lsbs_test();
    ord_test();
    to_hex_digit_tests();
    hex_to_number_test();
    swap_nibbles_test();
    rot_tests();
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
