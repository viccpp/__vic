// Unicode utilities
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_UNICODE_H
#define __VIC_UNICODE_H

#include<__vic/defs.h>
#if !__cpp_unicode_characters
#include<__vic/stdint.h>
#endif

namespace __vic {

// Unicode code point type
#if __cpp_unicode_characters
typedef char32_t unicode_t;
#else
typedef uint_least32_t unicode_t;
#endif

__VIC_CONSTEXPR_VAR unicode_t unicode_max = 0x10FFFF;
__VIC_CONSTEXPR_VAR unicode_t unicode_bom = 0xFEFF;
__VIC_CONSTEXPR_VAR unicode_t unicode_replacement_char = 0xFFFD;

} // namespace

#endif // header guard
