// Code point read result
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2024

#ifndef __VIC_UTF16_READ_RESULT_H
#define __VIC_UTF16_READ_RESULT_H

#include<__vic/unicode.h>
#include<__vic/utf16/defs.h>
#include<__vic/utf16/status.h>
#include<__vic/sreaders/result.h>

namespace __vic { namespace utf16 {

//////////////////////////////////////////////////////////////////////////////
// Internal implementation class
template<class T>
struct read_result_
{
    T value_;
    status_t status_;
public:
    read_result_(status_t s) : status_(s) {}
    read_result_(T v) : value_(v), status_(utf16::status::ok) {}

    T value() const { return value_; }
    status_t status() const { return status_; }
#if __cplusplus >= 201103L // C++11
    explicit operator bool() const { return status_ == utf16::status::ok; }
#else // C++98
    typedef const status_t read_result_::*unspecified_bool_type;
    operator unspecified_bool_type() const
    {
        return status_ == utf16::status::ok ? &read_result_::status_ : 0;
    }
#endif
};
//////////////////////////////////////////////////////////////////////////////
typedef read_result_<code_unit_t> read_unit_result;
typedef read_result_<unicode_t> read_result;

sread_result<unicode_t> convert_or_throw(read_result );

}} // namespace

#endif // header guard
