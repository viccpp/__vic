// UTF-8 core definitions
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2013

#ifndef __VIC_UTF8_DEFS_H
#define __VIC_UTF8_DEFS_H

#include<__vic/defs.h>
#include<__vic/unicode.h>

namespace __vic { namespace utf8 {

//----------------------------------------------------------------------------
// byte has form 10xxxxxx
inline bool is_continuation_byte(unsigned char b)
{
    return (b & 0xC0) == 0x80; // 10xxxxxx
}
//----------------------------------------------------------------------------
extern const unicode_t length_thresholds[5]; // internal variable

}} // namespace

#endif // header guard
