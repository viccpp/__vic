// UTF-16 exceptions
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_UTF16_EXCEPTIONS_H
#define __VIC_UTF16_EXCEPTIONS_H

#include<__vic/defs.h>
#include<exception>

namespace __vic { namespace utf16 {

//////////////////////////////////////////////////////////////////////////////
struct bad_encoding : public std::exception {};
struct truncated_code_unit : public bad_encoding
{
    const char *what() const noexcept;
};
struct truncated_code_point : public bad_encoding
{
    const char *what() const noexcept;
};
struct invalid_sequence : public bad_encoding
{
    const char *what() const noexcept;
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
