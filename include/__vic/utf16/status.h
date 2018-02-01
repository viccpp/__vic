// UTF-16 read status
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_UTF16_STATUS_H
#define __VIC_UTF16_STATUS_H

#include<__vic/defs.h>

namespace __vic { namespace utf16 {

//////////////////////////////////////////////////////////////////////////////
__VIC_SCOPED_ENUM_BEGIN(status)
{
    ok = 0,
    eof,
    // Errors
    truncated_code_unit,
    truncated_code_point,
    invalid_sequence
}
__VIC_SCOPED_ENUM_END(status)
//////////////////////////////////////////////////////////////////////////////
__VIC_CONSTEXPR_FUNC bool is_error(status_t s) { return s > status::eof; }

bool throw_if_error(status_t );

}} // namespace

#endif // header guard
