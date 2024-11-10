// Code point read result
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2024

#ifndef __VIC_UTF8_READ_RESULT_H
#define __VIC_UTF8_READ_RESULT_H

#include<__vic/unicode.h>
#include<__vic/utf8/status.h>
#include<__vic/sreaders/result.h>

namespace __vic { namespace utf8 {

//////////////////////////////////////////////////////////////////////////////
struct read_result
{
    unicode_t value_;
    status_t status_;
public:
    read_result(status_t s) : status_(s) {}
    read_result(unicode_t v) : value_(v), status_(utf8::status::ok) {}

    unicode_t value() const { return value_; }
    status_t status() const { return status_; }
#if __cplusplus >= 201103L // C++11
    explicit operator bool() const { return status_ == utf8::status::ok; }
#else // C++98
    typedef const status_t read_result::*unspecified_bool_type;
    operator unspecified_bool_type() const
    {
        return status_ == utf8::status::ok ? &read_result::status_ : 0;
    }
#endif
};
//////////////////////////////////////////////////////////////////////////////
sread_result<unicode_t> convert_or_throw(read_result );

}} // namespace

#endif // header guard
