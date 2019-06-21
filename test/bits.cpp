#include<__vic/bits.h>
#include<iostream>
#include<exception>
#include<cassert>

namespace tests {

//----------------------------------------------------------------------------
void nibble_tests()
{
    char ch = '\xFA';
    std::cout << std::hex << std::uppercase <<
        unsigned(__vic::hi_nibble(ch)) << ' ' <<
        unsigned(__vic::lo_nibble(ch)) << '\n';
    assert(__vic::hi_nibble(ch) == 0xF);
    assert(__vic::lo_nibble(ch) == 0xA);
}
//----------------------------------------------------------------------------
void ones_test()
{
    std::cout << __vic::lsb_ones<int>(5) << '\n';
    assert(__vic::lsb_ones<int>(5) == 0x1F);
    std::cout << unsigned(__vic::msb_ones<uint8_t>(5)) << '\n';
    assert(__vic::msb_ones<uint8_t>(5) == uint8_t('\xF8'));
}
//----------------------------------------------------------------------------
void get_lsbs_test()
{
    std::cout << __vic::get_lsbs(~int(0), 6) << '\n';
    assert(__vic::get_lsbs(~int(0), 6) == 0x3F);
}
//----------------------------------------------------------------------------
void ord_test()
{
    char ch = -20;
    std::cout << std::dec << __vic::ord(ch) << '\n';
    assert(__vic::ord(ch) == 236);
}
//----------------------------------------------------------------------------
void swap_nibbles_test()
{
    assert(__vic::swapped_nibbles(0x12) == 0x21);
}
//----------------------------------------------------------------------------
void rot_tests()
{
    assert(__vic::rotl(uint32_t(0x12345678), 8) == uint32_t(0x34567812));
    assert(__vic::rotr(uint32_t(0x12345678), 8) == uint32_t(0x78123456));
    // corner case
    const uint32_t v = 1;
    assert(__vic::rotl(v, 0) == v);
    assert(__vic::rotr(v, 0) == v);
}
//----------------------------------------------------------------------------
void popcount_tests()
{
    assert(__vic::popcount(0U) == 0);
    assert(__vic::popcount(1U) == 1);
    assert(__vic::popcount(0x11U) == 2);
    assert(__vic::popcount(0x1111U) == 4);
    assert(__vic::popcount(0x0FF0U) == 8);

    assert(__vic::popcount(0x11UL) == 2);
#ifdef __VIC_LONGLONG
    assert(__vic::popcount(static_cast<unsigned __VIC_LONGLONG>(0x11)) == 2);
#endif
    assert(__vic::popcount(static_cast<unsigned short>(0x11)) == 2);
    assert(__vic::popcount(static_cast<unsigned char>(0x11)) == 2);
}
//----------------------------------------------------------------------------
void msb_position_tests()
{
    assert(__vic::msb_position(1U) == 0);
    assert(__vic::msb_position(2U) == 1);
    assert(__vic::msb_position(0x10U) == 4);
    assert(__vic::msb_position(0x8000U) == 15);

    assert(__vic::msb_position(static_cast<unsigned long>(0x10)) == 4);
#ifdef __VIC_LONGLONG
    assert(__vic::msb_position(static_cast<unsigned __VIC_LONGLONG>(0x10)) == 4);
#endif
    assert(__vic::msb_position(static_cast<unsigned short>(0x10)) == 4);
    assert(__vic::msb_position(static_cast<unsigned char>(0x10)) == 4);
}
//----------------------------------------------------------------------------
void ispow2_tests()
{
    assert(!__vic::ispow2(0U));
    assert( __vic::ispow2(1U));
    assert( __vic::ispow2(2U));
    assert(!__vic::ispow2(3U));
    assert( __vic::ispow2(4U));
    assert(!__vic::ispow2(5U));
    assert( __vic::ispow2(8U));
    assert( __vic::ispow2(0x100U));

    assert(__vic::ispow2(static_cast<unsigned long>(2)));
#ifdef __VIC_LONGLONG
    assert(__vic::ispow2(static_cast<unsigned __VIC_LONGLONG>(2)));
#endif
    assert(__vic::ispow2(static_cast<unsigned short>(2)));
    assert(__vic::ispow2(static_cast<unsigned char>(2)));
}
//----------------------------------------------------------------------------
void ceil_log2_tests()
{
    assert(__vic::ceil_log2(0U) == 0);
    assert(__vic::ceil_log2(1U) == 0);
    assert(__vic::ceil_log2(2U) == 1);
    assert(__vic::ceil_log2(3U) == 2);
    assert(__vic::ceil_log2(4U) == 2);
    assert(__vic::ceil_log2(5U) == 3);
    assert(__vic::ceil_log2(0x11U) == 5);

    assert(__vic::ceil_log2(static_cast<unsigned long>(0x11)) == 5);
#ifdef __VIC_LONGLONG
    assert(__vic::ceil_log2(static_cast<unsigned __VIC_LONGLONG>(0x11)) == 5);
#endif
    assert(__vic::ceil_log2(static_cast<unsigned short>(0x11)) == 5);
    assert(__vic::ceil_log2(static_cast<unsigned char>(0x11)) == 5);
}
//----------------------------------------------------------------------------
void floor_log2_tests()
{
    assert(__vic::floor_log2(0U) == 0);
    assert(__vic::floor_log2(1U) == 0);
    assert(__vic::floor_log2(2U) == 1);
    assert(__vic::floor_log2(3U) == 1);
    assert(__vic::floor_log2(4U) == 2);
    assert(__vic::floor_log2(5U) == 2);
    assert(__vic::floor_log2(0xFFU) == 7);

    assert(__vic::floor_log2(static_cast<unsigned long>(0xFF)) == 7);
#ifdef __VIC_LONGLONG
    assert(__vic::floor_log2(static_cast<unsigned __VIC_LONGLONG>(0xFF)) == 7);
#endif
    assert(__vic::floor_log2(static_cast<unsigned short>(0xFF)) == 7);
    assert(__vic::floor_log2(static_cast<unsigned char>(0xFF)) == 7);
}
//----------------------------------------------------------------------------
void ceil2_tests()
{
    assert(__vic::ceil2(0U) == 1);
    assert(__vic::ceil2(1U) == 1);
    assert(__vic::ceil2(2U) == 2);
    assert(__vic::ceil2(3U) == 4);
    assert(__vic::ceil2(4U) == 4);
    assert(__vic::ceil2(5U) == 8);
    assert(__vic::ceil2(0x11U) == 0x20);

    assert(__vic::ceil2(static_cast<unsigned long>(0x11)) == 0x20);
#ifdef __VIC_LONGLONG
    assert(__vic::ceil2(static_cast<unsigned __VIC_LONGLONG>(0x11)) == 0x20);
#endif
    assert(__vic::ceil2(static_cast<unsigned short>(0x11)) == 0x20);
    assert(__vic::ceil2(static_cast<unsigned char>(0x11)) == 0x20);
}
//----------------------------------------------------------------------------
void floor2_tests()
{
    assert(__vic::floor2(0U) == 0);
    assert(__vic::floor2(1U) == 1);
    assert(__vic::floor2(2U) == 2);
    assert(__vic::floor2(3U) == 2);
    assert(__vic::floor2(4U) == 4);
    assert(__vic::floor2(5U) == 4);
    assert(__vic::floor2(0xFFU) == 0x80);

    assert(__vic::floor2(static_cast<unsigned long>(0xFF)) == 0x80);
#ifdef __VIC_LONGLONG
    assert(__vic::floor2(static_cast<unsigned __VIC_LONGLONG>(0xFF)) == 0x80);
#endif
    assert(__vic::floor2(static_cast<unsigned short>(0xFF)) == 0x80);
    assert(__vic::floor2(static_cast<unsigned char>(0xFF)) == 0x80);
}
//----------------------------------------------------------------------------
void run()
{
    nibble_tests();
    ones_test();
    get_lsbs_test();
    ord_test();
    swap_nibbles_test();
    rot_tests();
    popcount_tests();
    msb_position_tests();
    ispow2_tests();
    ceil_log2_tests();
    floor_log2_tests();
    ceil2_tests();
    floor2_tests();
}
//----------------------------------------------------------------------------

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
