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
#if defined(_MSC_VER) && defined(__VIC_POPCNT)
// __popcnt() call causes app crash if not supported by CPU
#include<intrin.h>
#endif

#if __cpp_static_assert
#define __VIC_ASSERT_UINT(T) \
    static_assert(T(-1) > 0, "Unsigned type is required")
#else
#define __VIC_ASSERT_UINT(T) \
    typedef char assert_argument_is_unsigned[T(-1) > 0 ? 1 : -1]
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
__VIC_CONSTEXPR_FUNC T msb_ones(unsigned bits_num)
{
    return ~T(0) << (sizeof(T) * CHAR_BIT - bits_num);
}
//------------------------------------------------------------------------------
// Returns value with all least significant bits are 1 (others - 0)
// Parameter specifies the number of "ones"
template<class T>
__VIC_CONSTEXPR_FUNC T lsb_ones(unsigned bits_num)
{
    return ~(~T(0) << bits_num);
}
//------------------------------------------------------------------------------
// Clears all but bits_num least significant bits
template<class T>
__VIC_CONSTEXPR_FUNC T get_lsbs(T v, unsigned bits_num)
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
    for(; v; v >>= 1) c += v & 1U;
    return c;
}
//----------------------------------------------------------------------------
inline unsigned popcount(unsigned v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUILTINS)
    return __builtin_popcount(v);
#elif defined(_MSC_VER) && defined(__VIC_POPCNT)
    return __popcnt(v);
#else
    return popcount_uint(v);
#endif
}
//----------------------------------------------------------------------------
inline unsigned popcount(unsigned long v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUILTINS)
    return __builtin_popcountl(v);
#elif defined(_MSC_VER) && defined(__VIC_POPCNT)
    return __popcnt(v); // sizeof(unsigned long) == sizeof(unsigned) on Windows
#else
    return popcount_uint(v);
#endif
}
//----------------------------------------------------------------------------
#ifdef __VIC_LONGLONG
inline unsigned popcount(unsigned __VIC_LONGLONG v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUILTINS)
    return __builtin_popcountll(v);
#elif defined(_MSC_VER) && defined(__VIC_POPCNT)
#ifdef _WIN64
    return static_cast<unsigned>(__popcnt64(v));
#else // __popcnt64() is not available on 32-bit MSVC++
    return __popcnt(static_cast<unsigned>(v)) + __popcnt(v >> 32);
#endif
#else
    return popcount_uint(v);
#endif
}
#endif
//----------------------------------------------------------------------------
inline unsigned popcount(unsigned short v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUILTINS)
    return __builtin_popcount(v);
#elif defined(_MSC_VER) && defined(__VIC_POPCNT)
    return __popcnt16(v);
#else
    return popcount_uint(v);
#endif
}
//----------------------------------------------------------------------------
inline unsigned popcount(unsigned char v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUILTINS)
    return __builtin_popcount(v);
#elif defined(_MSC_VER) && defined(__VIC_POPCNT)
    return __popcnt16(v);
#else
    return popcount_uint(v);
#endif
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Returns position of the most significant 1-bit
// Precondition: v != 0
template<class UInt>
inline unsigned msb_position_uint(UInt v)
{
    __VIC_ASSERT_UINT(UInt);
    unsigned c = 0;
    while(v >>= 1) c++;
    return c;
}
//----------------------------------------------------------------------------
inline unsigned msb_position(unsigned v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUILTINS)
    return unsigned(sizeof(v) * CHAR_BIT) - __builtin_clz(v) - 1U;
#else
    return msb_position_uint(v);
#endif
}
//----------------------------------------------------------------------------
inline unsigned msb_position(unsigned long v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUILTINS)
    return unsigned(sizeof(v) * CHAR_BIT) - __builtin_clzl(v) - 1U;
#else
    return msb_position_uint(v);
#endif
}
//----------------------------------------------------------------------------
#ifdef __VIC_LONGLONG
inline unsigned msb_position(unsigned __VIC_LONGLONG v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUILTINS)
    return unsigned(sizeof(v) * CHAR_BIT) - __builtin_clzll(v) - 1U;
#else
    return msb_position_uint(v);
#endif
}
#endif
//----------------------------------------------------------------------------
inline unsigned msb_position(unsigned short v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUILTINS)
    return msb_position(static_cast<unsigned>(v));
#else
    return msb_position_uint(v);
#endif
}
//----------------------------------------------------------------------------
inline unsigned msb_position(unsigned char v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUILTINS)
    return msb_position(static_cast<unsigned>(v));
#else
    return msb_position_uint(v);
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
inline unsigned rotl(unsigned v, int sh) { return rotl_uint(v, sh); }
inline unsigned long rotl(unsigned long v, int sh) { return rotl_uint(v, sh); }
inline unsigned short rotl(unsigned short v, int sh) { return rotl_uint(v, sh); }
inline unsigned char rotl(unsigned char v, int sh) { return rotl_uint(v, sh); }
//----------------------------------------------------------------------------
inline unsigned rotr(unsigned v, int sh) { return rotr_uint(v, sh); }
inline unsigned long rotr(unsigned long v, int sh) { return rotr_uint(v, sh); }
inline unsigned short rotr(unsigned short v, int sh) { return rotr_uint(v, sh); }
inline unsigned char rotr(unsigned char v, int sh) { return rotr_uint(v, sh); }
//----------------------------------------------------------------------------
#ifdef __VIC_LONGLONG
inline unsigned __VIC_LONGLONG rotl(unsigned __VIC_LONGLONG v, int sh)
{
    return rotl_uint(v, sh);
}
inline unsigned __VIC_LONGLONG rotr(unsigned __VIC_LONGLONG v, int sh)
{
    return rotr_uint(v, sh);
}
#endif
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template<class UInt>
inline bool ispow2(UInt n)
{
    __VIC_ASSERT_UINT(UInt);
#if 1
    return popcount(n) == 1U;
#else // universal implementation w/o popcount()
    return n != 0U && (n & (n - 1U)) == 0U;
#endif
}
//----------------------------------------------------------------------------
template<class UInt>
inline unsigned ceil_log2(UInt n)
{
    __VIC_ASSERT_UINT(UInt);
    return n >> 1 ? msb_position(UInt(n - 1U)) + 1U : 0U;
}
//----------------------------------------------------------------------------
template<class UInt>
inline unsigned floor_log2(UInt n)
{
    __VIC_ASSERT_UINT(UInt);
    return n ? msb_position(n) : 0U;
}
//----------------------------------------------------------------------------
// Returns the number x: ispow2(x) && x >= n
template<class UInt>
inline UInt ceil2(UInt n)
{
    __VIC_ASSERT_UINT(UInt);
    if(n == 0U || n == 1U) return 1U;
    return UInt(1) << (msb_position(UInt(n - 1U)) + 1U);
}
//----------------------------------------------------------------------------
// If n != 0 returns the number x: ispow2(x) && x <= n
// Otherwise 0 is returned
template<class UInt>
inline UInt floor2(UInt n)
{
    __VIC_ASSERT_UINT(UInt);
    return n ? UInt(1) << msb_position(n) : 0U;
}
//----------------------------------------------------------------------------

#undef __VIC_ASSERT_UINT

} // namespace

#endif // header guard
