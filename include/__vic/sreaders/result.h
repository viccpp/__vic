// sreader::operator() result type
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2021

#ifndef __VIC_SREADERS_RESULT_H
#define __VIC_SREADERS_RESULT_H

#include<__vic/defs.h>
#include<__vic/sreaders/defs.h>

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
template<>
struct sread_result<unsigned char>
{
    unsigned char value_;
    bool ok_; // !EOF
public:
    sread_result() : ok_(false) {}
    sread_result(sread_eof_t) : ok_(false) {}
    sread_result(unsigned char v) : value_(v), ok_(true) {}

    // Implicit converters
    sread_result(sread_result<char> r) : value_(r.value()), ok_(r) {}
#if __cpp_lib_byte // C++17
    sread_result(sread_result<std::byte> r)
        : value_(static_cast<unsigned char>(r.value())), ok_(r) {}
#endif
#if __cpp_char8_t // C++20
    sread_result(sread_result<char8_t> r) : value_(r.value()), ok_(r) {}
#endif

    unsigned char value() const { return value_; }
#if __cplusplus >= 201103L // C++11
    explicit operator bool() const { return ok_; }
#else // C++98
    typedef const bool sread_result::*unspecified_bool_type;
    operator unspecified_bool_type() const
        { return ok_ ? &sread_result::ok_ : 0; }
#endif
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline unsigned char uchar_value(sread_result<unsigned char> r)
{
    return r.value();
}
//----------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
template<class T>
struct sreader_value<sread_result<T> >
{
    typedef T type;
};
//////////////////////////////////////////////////////////////////////////////

#if __cplusplus >= 201103L // C++11
#define __VIC_SREAD_RESULT(T) auto
#else // C++98
#define __VIC_SREAD_RESULT(T) ::__vic::sread_result<T>
#endif

} // namespace

#endif // header guard
