// Bits/bytes manipulation tools
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_BITS_H
#define __VIC_BITS_H

#include<__vic/defs.h>
#include<__vic/stdint.h>
#include<climits>
#if defined(_MSC_VER) && !defined(__VIC_NO_BUITLINS)
#include<intrin.h>
#endif

#if __cpp_static_assert
#define __VIC_ASSERT_UINT(T) \
    static_assert(T(-1) > 0, "Unsigned type is required")
#else
#define __VIC_ASSERT_UINT(T) \
    typedef char assert_argument_is_unsigned[T(-1) > 0 : 1 : -1]
#endif

namespace __vic {

//----------------------------------------------------------------------------
// Returns low-order nibble (or tetrad, or half-byte) of the byte
__VIC_CONSTEXPR_FUNC uint8_t lo_nibble(uint8_t b)
{
    return b & 0x0F;
}
//----------------------------------------------------------------------------
// Returns high-order nibble (or tetrad, or half-byte) of the byte
__VIC_CONSTEXPR_FUNC uint8_t hi_nibble(uint8_t b)
{
    return b >> 4;
}
//------------------------------------------------------------------------------
// Returns value with all most significant bits are 1 (others - 0)
// Parameter specifies the number of "ones"
template<class T>
inline T msb_ones(unsigned bits_num)
{
    return ~T(0) << (sizeof(T) * CHAR_BIT - bits_num);
}
//------------------------------------------------------------------------------
// Returns value with all least significant bits are 1 (others - 0)
// Parameter specifies the number of "ones"
template<class T>
inline T lsb_ones(unsigned bits_num)
{
    return ~(~T(0) << bits_num);
}
//------------------------------------------------------------------------------
// Clears all but bits_num least significant bits
template<class T>
inline T get_lsbs(T v, unsigned bits_num)
{
    return v & lsb_ones<T>(bits_num);
}
//----------------------------------------------------------------------------
// Returns char code 0..255
__VIC_CONSTEXPR_FUNC int ord(char ch)
{
    return static_cast<unsigned char>(ch);
}
//----------------------------------------------------------------------------
// Swap high-order nibble with low-order one
__VIC_CONSTEXPR_FUNC uint8_t swapped_nibbles(uint8_t b)
{
    return (b << 4) | (b >> 4);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Counts 1-bits
template<class UInt>
__VIC_CONSTEXPR14 unsigned popcount_uint(UInt v)
{
    __VIC_ASSERT_UINT(UInt);
    unsigned c = 0;
    for(; v; v >>= 1) c += v & 1;
    return c;
}
//----------------------------------------------------------------------------
inline unsigned popcount(unsigned v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUITLINS)
    return __builtin_popcount(v);
#elif defined(_MSC_VER) && !defined(__VIC_NO_BUITLINS)
    return __popcnt(v);
#else
    return popcount_uint(v);
#endif
}
//----------------------------------------------------------------------------
inline unsigned popcount(unsigned long v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUITLINS)
    return __builtin_popcountl(v);
#else
    return popcount_uint(v);
#endif
}
//----------------------------------------------------------------------------
#ifdef __VIC_LONGLONG
inline unsigned popcount(unsigned __VIC_LONGLONG v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUITLINS)
    return __builtin_popcountll(v);
#elif defined(_MSC_VER) && !defined(__VIC_NO_BUITLINS)
    return static_cast<unsigned>(__popcnt64(v));
#else
    return popcount_uint(v);
#endif
}
#endif
//----------------------------------------------------------------------------
inline unsigned popcount(unsigned short v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUITLINS)
    return __builtin_popcount(v);
#else
    return popcount_uint(v);
#endif
}
//----------------------------------------------------------------------------
inline unsigned popcount(unsigned char v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUITLINS)
    return __builtin_popcount(v);
#else
    return popcount_uint(v);
#endif
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template<class UInt>
inline UInt rotl_uint(UInt v, int shift)
{
    const int w = sizeof(UInt) * CHAR_BIT; // width in bits
    //return (v << shift) | (v >> (w - shift)); // UB if shift == 0
    return (v << shift) | (v >> ((w - shift) & (w - 1)));
}
//----------------------------------------------------------------------------
template<class UInt>
inline UInt rotr_uint(UInt v, int shift)
{
    const int w = sizeof(UInt) * CHAR_BIT; // width in bits
    //return (v >> shift) | (v << (w - shift)); // UB if shift == 0
    return (v >> shift) | (v << ((w - shift) & (w - 1)));
}
//----------------------------------------------------------------------------
inline uint8_t  rotl(uint8_t  v, int sh) { return rotl_uint(v, sh); }
inline uint16_t rotl(uint16_t v, int sh) { return rotl_uint(v, sh); }
inline uint32_t rotl(uint32_t v, int sh) { return rotl_uint(v, sh); }
inline uint64_t rotl(uint64_t v, int sh) { return rotl_uint(v, sh); }
//----------------------------------------------------------------------------
inline uint8_t  rotr(uint8_t  v, int sh) { return rotr_uint(v, sh); }
inline uint16_t rotr(uint16_t v, int sh) { return rotr_uint(v, sh); }
inline uint32_t rotr(uint32_t v, int sh) { return rotr_uint(v, sh); }
inline uint64_t rotr(uint64_t v, int sh) { return rotr_uint(v, sh); }
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
