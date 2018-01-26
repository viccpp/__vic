// UTF-8 read status
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2013

#ifndef __VIC_UTF8_STATUS_H
#define __VIC_UTF8_STATUS_H

#include<__vic/defs.h>

namespace __vic { namespace utf8 {

//////////////////////////////////////////////////////////////////////////////
__VIC_SCOPED_ENUM_BEGIN(status)
{
    ok = 0,
    eof,
    // Errors
    no_leading_byte,
    truncated_code_point,
    overlong_encoding,
    code_point_too_big
}
__VIC_SCOPED_ENUM_END(status)
//////////////////////////////////////////////////////////////////////////////
__VIC_CONSTEXPR_FUNC bool is_error(status_t s) { return s > status::eof; }

bool throw_if_error(status_t );

}} // namespace

#endif // header guard
