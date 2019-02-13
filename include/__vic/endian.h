// Byte order-related utilities
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2016

#ifndef __VIC_ENDIAN_H
#define __VIC_ENDIAN_H

#include<__vic/stdint.h>

namespace __vic {

//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC uint16_t swab16(uint16_t v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_GCC_BUITLINS) && \
        (__GNUC__ > 4 || __GNUC__ == 4 && __GNUC_MINOR__ >= 8)
    return __builtin_bswap16(v);
#else
    return (v << 8) | (v >> 8);
#endif
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC uint32_t swab32(uint32_t v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_GCC_BUITLINS)
    return __builtin_bswap32(v);
#else
    return (v >> 24) | ((v & uint32_t(0x00FF0000)) >> 8) |
        ((v & uint32_t(0x0000FF00)) << 8) | (v << 24);
#endif
}
//----------------------------------------------------------------------------
__VIC_CONSTEXPR_FUNC uint64_t swab64(uint64_t v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_GCC_BUITLINS)
    return __builtin_bswap64(v);
#else
    return (v >> 56) |
        ((v >> 40) & (uint64_t(0xFF) <<  8)) |
        ((v >> 24) & (uint64_t(0xFF) << 16)) |
        ((v >> 8 ) & (uint64_t(0xFF) << 24)) |
        ((v << 8 ) & (uint64_t(0xFF) << 32)) |
        ((v << 24) & (uint64_t(0xFF) << 40)) |
        ((v << 40) & (uint64_t(0xFF) << 48)) |
        (v << 56);
#endif
}
//----------------------------------------------------------------------------

namespace endian {

//////////////////////////////////////////////////////////////////////////////
enum endianness
{
    unknown = 0,
    little = 1234,
    big    = 4321,
    pdp    = 3412,
    native =
#ifdef __BYTE_ORDER__
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        little
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        big
//#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
        // there are no such platforms anymore
#endif // __BYTE_ORDER__
#elif defined(_WIN32)
        little
#else
        unknown
#endif
};
//////////////////////////////////////////////////////////////////////////////

} // namespace

using endian::endianness;

} // namespace

#endif // header guard
