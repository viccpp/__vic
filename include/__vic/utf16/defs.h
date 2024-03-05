// UTF-16 core definitions
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_UTF16_DEFS_H
#define __VIC_UTF16_DEFS_H

#include<__vic/defs.h>
#if !__cpp_unicode_characters
#include<__vic/stdint.h>
#endif

namespace __vic { namespace utf16 {

// UTF-16 code unit type
#if __cpp_unicode_characters
typedef char16_t code_unit_t;
#else
typedef uint_least16_t code_unit_t;
#endif

// Leading (high) surrogates
__VIC_INLINE_CONSTEXPR_VAR code_unit_t hi_surrogate_min = 0xD800,
                                       hi_surrogate_max = 0xDBFF;
// Trailing (low) surrogates
__VIC_INLINE_CONSTEXPR_VAR code_unit_t lo_surrogate_min = 0xDC00,
                                       lo_surrogate_max = 0xDFFF;

}} // namespace

#endif // header guard
