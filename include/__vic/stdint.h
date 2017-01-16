// Some ISO C99/C++11 integer types + Generic integer types
// This file introduces definitions to the global namespace!
//
// Platform: ISO C++98/11
// $Id$
//
// (c) __vic 2006

#ifndef __VIC_STDINT_H
#define __VIC_STDINT_H

#include<__vic/defs.h>

#if __cplusplus >= 201103L

#include<cstdint>

#elif defined(_MSC_VER) && _MSC_VER < 1600 || \
    defined(__BORLANDC__) && __BORLANDC__ < 0x0580

// Exact-width integer types
typedef signed char int8_t;
typedef short int   int16_t;
typedef int         int32_t;
typedef __int64     int64_t;

typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned __int64    uint64_t;

// Minimum-width integer types
typedef int8_t      int_least8_t;
typedef int16_t     int_least16_t;
typedef int32_t     int_least32_t;
typedef int64_t     int_least64_t;

typedef uint8_t     uint_least8_t;
typedef uint16_t    uint_least16_t;
typedef uint32_t    uint_least32_t;
typedef uint64_t    uint_least64_t;

// Fastest minimum-width integer types
typedef int8_t      int_fast8_t;
typedef int32_t     int_fast16_t;
typedef int32_t     int_fast32_t;
typedef int64_t     int_fast64_t;

typedef uint8_t     uint_fast8_t;
typedef uint32_t    uint_fast16_t;
typedef uint32_t    uint_fast32_t;
typedef uint64_t    uint_fast64_t;

// Integer types capable of holding object pointers
// See below...
#define __VIC_NEED_INTPTR_T 1

// Greatest-width integer types
typedef int64_t     intmax_t;
typedef uint64_t    uintmax_t;

#else // just redirect to the system header

#if defined(__FreeBSD__) || defined(__IBMCPP__) || defined(_AIX)
#include<inttypes.h>
#else
#include<stdint.h>
#endif

#endif

namespace __vic {

// Integers with exactly specified size
template<unsigned > struct int_exactly_bytes; // not defined
template<unsigned > struct uint_exactly_bytes; // not defined

// Specializations
template<> struct int_exactly_bytes<1U> { typedef int8_t type; };
template<> struct int_exactly_bytes<2U> { typedef int16_t type; };
template<> struct int_exactly_bytes<4U> { typedef int32_t type; };
template<> struct int_exactly_bytes<8U> { typedef int64_t type; };

template<> struct uint_exactly_bytes<1U> { typedef uint8_t type; };
template<> struct uint_exactly_bytes<2U> { typedef uint16_t type; };
template<> struct uint_exactly_bytes<4U> { typedef uint32_t type; };
template<> struct uint_exactly_bytes<8U> { typedef uint64_t type; };

#if __cpp_alias_templates
template<unsigned N> using int_exact_bytes = typename int_exactly_bytes<N>::type;
template<unsigned N> using uint_exact_bytes = typename uint_exactly_bytes<N>::type;
#endif

} // namespace

#ifdef __VIC_NEED_INTPTR_T
typedef __vic::int_exactly_bytes<sizeof(void*)>::type intptr_t;
typedef __vic::uint_exactly_bytes<sizeof(void*)>::type uintptr_t;
#undef __VIC_NEED_INTPTR_T
#endif

#endif // __VIC_STDINT_H
