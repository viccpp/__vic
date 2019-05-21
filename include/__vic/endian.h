// Byte order-related utilities
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2016

#ifndef __VIC_ENDIAN_H
#define __VIC_ENDIAN_H

#include<__vic/defs.h>
#include<__vic/stdint.h>

namespace __vic {

//----------------------------------------------------------------------------
__VIC_NODISCARD __VIC_CONSTEXPR_FUNC uint16_t swab16(uint16_t v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUITLINS) && \
        (__GNUC__ > 4 || __GNUC__ == 4 && __GNUC_MINOR__ >= 8)
    return __builtin_bswap16(v);
#else
    return (v << 8) | (v >> 8);
#endif
}
//----------------------------------------------------------------------------
__VIC_NODISCARD __VIC_CONSTEXPR_FUNC uint32_t swab32(uint32_t v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUITLINS)
    return __builtin_bswap32(v);
#else
    return (v >> 24) | ((v & uint32_t(0x00FF0000)) >> 8) |
        ((v & uint32_t(0x0000FF00)) << 8) | (v << 24);
#endif
}
//----------------------------------------------------------------------------
__VIC_NODISCARD __VIC_CONSTEXPR_FUNC uint64_t swab64(uint64_t v)
{
#if defined(__GNUC__) && !defined(__VIC_NO_BUITLINS)
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

//----------------------------------------------------------------------------
template<class T, size_t = sizeof(T)>
struct bytes_inverter; // not defined
//----------------------------------------------------------------------------
template<class T>
struct bytes_inverter<T,1>
{
    static __VIC_CONSTEXPR_FUNC T value(T v)
    {
        return v;
    }
};
//----------------------------------------------------------------------------
template<class T>
struct bytes_inverter<T,2>
{
    static __VIC_CONSTEXPR_FUNC T value(T v)
    {
        return static_cast<T>(swab16(static_cast<uint16_t>(v)));
    }
};
//----------------------------------------------------------------------------
template<class T>
struct bytes_inverter<T,4>
{
    static __VIC_CONSTEXPR_FUNC T value(T v)
    {
        return static_cast<T>(swab32(static_cast<uint32_t>(v)));
    }
};
//----------------------------------------------------------------------------
template<class T>
struct bytes_inverter<T,8>
{
    static __VIC_CONSTEXPR_FUNC T value(T v)
    {
        return static_cast<T>(swab64(static_cast<uint64_t>(v)));
    }
};
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

//----------------------------------------------------------------------------
template<endianness From, endianness To>
struct transformer; // not defined
//----------------------------------------------------------------------------
template<endianness E>
struct transformer<E,E> // same endianness
{
    template<class T> static __VIC_CONSTEXPR_FUNC T value(T v)
    {
        return v;
    }
};
//----------------------------------------------------------------------------
template<>
struct transformer<little,big>
{
    template<class T> static __VIC_CONSTEXPR_FUNC T value(T v)
    {
        return bytes_inverter<T>::value(v);
    }
};
//----------------------------------------------------------------------------
template<>
struct transformer<big,little>
{
    template<class T> static __VIC_CONSTEXPR_FUNC T value(T v)
    {
        return bytes_inverter<T>::value(v);
    }
};
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template<class T>
__VIC_NODISCARD __VIC_CONSTEXPR_FUNC T from_big(T v)
{
    return transformer<big,native>::value(v);
}
//----------------------------------------------------------------------------
template<class T>
__VIC_NODISCARD __VIC_CONSTEXPR_FUNC T from_little(T v)
{
    return transformer<little,native>::value(v);
}
//----------------------------------------------------------------------------
template<class T>
__VIC_NODISCARD __VIC_CONSTEXPR_FUNC T to_big(T v)
{
    return transformer<native,big>::value(v);
}
//----------------------------------------------------------------------------
template<class T>
__VIC_NODISCARD __VIC_CONSTEXPR_FUNC T to_little(T v)
{
    return transformer<native,little>::value(v);
}
//----------------------------------------------------------------------------

} // namespace

using endian::endianness;

} // namespace

#endif // header guard
