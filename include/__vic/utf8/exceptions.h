// UTF-8 exceptions
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2013

#ifndef __VIC_UTF8_EXCEPTIONS_H
#define __VIC_UTF8_EXCEPTIONS_H

#include<__vic/defs.h>
#include<exception>

namespace __vic { namespace utf8 {

//////////////////////////////////////////////////////////////////////////////
struct bad_encoding : public std::exception {};
struct no_leading_byte : public bad_encoding
{
    const char *what() const noexcept;
};
struct truncated_code_point : public bad_encoding
{
    const char *what() const noexcept;
};
struct overlong_encoding : public bad_encoding
{
    const char *what() const noexcept;
};
struct code_point_too_big : public bad_encoding
{
    const char *what() const noexcept;
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
