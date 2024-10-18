// sreader::operator() result type
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2021

#ifndef __VIC_SREADERS_RESULT_H
#define __VIC_SREADERS_RESULT_H

#include<__vic/defs.h>
#include<utility>

namespace __vic {

struct sread_eof_t
{
#if __cpp_initializer_lists
    explicit sread_eof_t() = default;
#endif
};
__VIC_INLINE_CONSTEXPR_VAR sread_eof_t sread_eof = sread_eof_t();

//////////////////////////////////////////////////////////////////////////////
template<class T>
struct sread_result
{
    // Public for structured bindings only
    T value_;
    bool ok_; // !EOF
public:
    sread_result() : ok_(false) {}
    sread_result(sread_eof_t) : ok_(false) {}
    sread_result(T v) : value_(v), ok_(true) {}

    T value() const { return value_; }
#if __cplusplus >= 201103L // C++11
    explicit operator bool() const { return ok_; }
#else // C++98
    typedef const bool sread_result::*unspecified_bool_type;
    operator unspecified_bool_type() const
        { return ok_ ? &sread_result::ok_ : 0; }
#endif
};
//////////////////////////////////////////////////////////////////////////////
struct sread_byte_result
{
    unsigned char value_;
    bool ok_; // !EOF

    sread_byte_result() : ok_(false) {}
    sread_byte_result(sread_eof_t) : ok_(false) {}
    sread_byte_result(unsigned char v) : value_(v), ok_(true) {}
    sread_byte_result(sread_result<unsigned char> r) : value_(r.value()), ok_(r) {}
    sread_byte_result(char v) : value_(v), ok_(true) {}
    sread_byte_result(sread_result<char> r) : value_(r.value()), ok_(r) {}
#if __cpp_lib_byte // C++17
    sread_byte_result(std::byte v)
        : value_(static_cast<unsigned char>(v)), ok_(true) {}
    sread_byte_result(sread_result<std::byte> r)
        : value_(static_cast<unsigned char>(r.value())), ok_(r) {}
#endif
#if __cpp_char8_t // C++20
    sread_byte_result(char8_t v) : value_(v), ok_(true) {}
    sread_byte_result(sread_result<char8_t> r) : value_(r.value()), ok_(r) {}
#endif

    unsigned char value() const { return value_; }
#if __cplusplus >= 201103L // C++11
    explicit operator bool() const { return ok_; }
#else // C++98
    typedef const bool sread_byte_result::*unspecified_bool_type;
    operator unspecified_bool_type() const
        { return ok_ ? &sread_byte_result::ok_ : 0; }
#endif
};
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
template<class SReadResult>
struct sread_value
{
#if __cpp_decltype
    typedef decltype(std::declval<SReadResult>().value) type;
#endif
};
//////////////////////////////////////////////////////////////////////////////
template<class T>
struct sread_value<sread_result<T> >
{
    typedef T type;
};
//////////////////////////////////////////////////////////////////////////////
template<>
struct sread_value<sread_byte_result>
{
    typedef unsigned char type;
};
//////////////////////////////////////////////////////////////////////////////
#if __cpp_alias_templates
template<class SReadResult>
using sread_value_t = typename sread_value<SReadResult>::type;
#endif
//////////////////////////////////////////////////////////////////////////////

#if __cplusplus >= 201103L // C++11
#define __VIC_SREAD_RESULT(T) auto
#define __VIC_SREAD_BYTE_RESULT auto
#else // C++98
#define __VIC_SREAD_RESULT(T) ::__vic::sread_result<T>
#define __VIC_SREAD_BYTE_RESULT ::__vic::sread_byte_result
#endif

} // namespace

#endif // header guard
