// String to number conversion utilities
//
// Platform: ISO C++ 98/11/17
// $Id$
//
// (c) __vic 2010

#ifndef __VIC_STR2NUM_H
#define __VIC_STR2NUM_H

#include<__vic/defs.h>
#include<__vic/ascii.h>
#include<__vic/type_traits.h>
#include<string>
#include<limits>
#if __has_include(<string_view>)
#include<string_view>
#endif
#if !__cpp_lib_string_view
#include<__vic/tchar.h>
#endif

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
__VIC_SCOPED_ENUM_UT_BEGIN(number_parse_status, unsigned char)
{
    ok,
    invalid_number,
    unrepresentable
}
__VIC_SCOPED_ENUM_END(number_parse_status)
//////////////////////////////////////////////////////////////////////////////
template<class T>
class number_parse_result
{
    T val;
    number_parse_status_t st;
public:
    typedef T value_type;

    number_parse_result(number_parse_status_t s) : st(s) {}
    explicit number_parse_result(T n) : val(n), st(number_parse_status::ok) {}

    number_parse_status_t status() const { return st; }
    T value() const { return val; }
    bool has_value() const { return st == number_parse_status::ok; }
#if __cplusplus >= 201103L
    explicit operator bool() const { return has_value(); }
#else
    typedef number_parse_status_t number_parse_result::*unspecified_bool_type;
    operator unspecified_bool_type() const
        { return has_value() ? &number_parse_result::st : 0; }
#endif
};
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
template<class UInt, class InputIterator>
__VIC_NODISCARD typename
enable_if<is_unsigned_integer<UInt>::value, number_parse_result<UInt> >::type
parse_decimal(InputIterator begin, InputIterator end)
{
    typedef number_parse_status st;
    if(begin == end) return st::invalid_number;

    // decs - count of full decades in the maximum value
    // ones - count of the rest ones in the maximum value
    __VIC_CONSTEXPR_VAR UInt decs = std::numeric_limits<UInt>::max() / UInt(10),
                             ones = std::numeric_limits<UInt>::max() % UInt(10);
    UInt res = 0;
    do {
        char c = *begin++;
        if(!ascii::isdigit(c)) return st::invalid_number;
        UInt dig = c - '0';
        // check if the next increment will cause overflow
        if(res > decs || (res == decs && dig > ones))
            return st::unrepresentable;
        res *= UInt(10); // decimal left shift (one digit)
        res += dig;
    } while(begin != end);
    return number_parse_result<UInt>(res);
}
//----------------------------------------------------------------------------
template<class Int, class InputIterator>
__VIC_NODISCARD typename
enable_if<is_signed_integer<Int>::value, number_parse_result<Int> >::type
parse_decimal(InputIterator begin, InputIterator end)
{
    typedef number_parse_status st;
    if(begin == end) return st::invalid_number;

    // decs - count of full decades in the maximum value
    // ones - count of the rest ones in the maximum value
    __VIC_CONSTEXPR_VAR Int decs = std::numeric_limits<Int>::max() / Int(10),
                            ones = std::numeric_limits<Int>::max() % Int(10);
    bool negative = false;
    switch(*begin)
    {
        case '-':
            negative = true;
            __VIC_FALLTHROUGH
        case '+':
            if(++begin == end) return st::invalid_number;
    }
    Int res = 0;
    do {
        char c = *begin++;
        if(!ascii::isdigit(c)) return st::invalid_number;
        Int dig = c - '0';
        // check if the next increment will cause overflow
        if(res > decs) return st::unrepresentable;
        else if(res == decs && dig > ones)
        {
            // cut off the minimal negative case
            if(negative && dig == ones + 1 && begin == end)
                return number_parse_result<Int>(std::numeric_limits<Int>::min());
            return st::unrepresentable;
        }
        res *= Int(10);
        res += dig;
    } while(begin != end);
    return number_parse_result<Int>(negative ? -res : res);
}
//----------------------------------------------------------------------------

#if __cpp_lib_string_view // C++17
//----------------------------------------------------------------------------
template<class T>
__VIC_NODISCARD inline
number_parse_result<T> parse_decimal(std::string_view s)
{
    return parse_decimal<T>(s.data(), s.data() + s.length());
}
//----------------------------------------------------------------------------
#else
//----------------------------------------------------------------------------
template<class T>
__VIC_NODISCARD inline
number_parse_result<T> parse_decimal(const std::string &s)
{
    return parse_decimal<T>(s.data(), &*s.end());
}
//----------------------------------------------------------------------------
template<class T>
__VIC_NODISCARD inline
number_parse_result<T> parse_decimal(const char *s)
{
    return s ? parse_decimal<T>(s, tchar::end(s))
             : number_parse_status::invalid_number;
}
//----------------------------------------------------------------------------
#endif

//////////////////////////////////////////////////////////////////////////////
template<class T>
class decimal_parser
{
    T res;
    typedef number_parse_status_t status;
    typedef number_parse_status st;
public:
    template<class InputIterator>
    __VIC_NODISCARD status parse(InputIterator begin, InputIterator end)
    {
        number_parse_result<T> r = parse_decimal<T>(begin, end);
        if(r) res = r.value();
        return r.status();
    }
#if __cpp_lib_string_view // C++17
    __VIC_NODISCARD status parse(std::string_view s)
        { return parse(s.data(), s.data() + s.length()); }
#else
    __VIC_NODISCARD status parse(const std::string &s)
        { return parse(s.data(), &*s.end()); }
    __VIC_NODISCARD status parse(const char *s)
        { return s ? parse(s, tchar::end(s)) : st::invalid_number; }
#endif
    __VIC_NODISCARD T result() const { return res; }
};
//////////////////////////////////////////////////////////////////////////////

namespace impl {
//----------------------------------------------------------------------------
__VIC_NORETURN void throw_empty_integer();
__VIC_NORETURN void throw_null_integer();
__VIC_NORETURN void throw_non_digit_char();
__VIC_NORETURN void throw_integer_too_long();
//----------------------------------------------------------------------------
} // namespace

//----------------------------------------------------------------------------
// String to number conversion with strict format control
//----------------------------------------------------------------------------
template<class T>
__VIC_NODISCARD T decimal_to_number(
#if __cpp_lib_string_view // C++17
    std::string_view
#else
    const std::string &
#endif
    s)
{
    number_parse_result<T> r = parse_decimal<T>(s);
    switch(r.status())
    {
        case number_parse_status::ok:
            return r.value();
        case number_parse_status::invalid_number:
            if(s.empty()) impl::throw_empty_integer();
            else impl::throw_non_digit_char();
        case number_parse_status::unrepresentable:
            impl::throw_integer_too_long();
    }
    return T(); // UNREACHABLE! Only to suppress spurious warning
}
//----------------------------------------------------------------------------
template<class T, class InputIterator>
__VIC_NODISCARD T decimal_to_number_range(InputIterator begin, InputIterator end)
{
    number_parse_result<T> r = parse_decimal<T>(begin, end);
    switch(r.status())
    {
        case number_parse_status::ok:
            return r.value();
        case number_parse_status::invalid_number:
            if(begin == end) impl::throw_empty_integer();
            else impl::throw_non_digit_char();
        case number_parse_status::unrepresentable:
            impl::throw_integer_too_long();
    }
    return T(); // UNREACHABLE! Only to suppress spurious warning
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// The same functions with the result as 2nd out argument
//----------------------------------------------------------------------------
template<class T>
inline void decimal_to_number(
#if __cpp_lib_string_view // C++17
    std::string_view
#else
    const std::string &
#endif
    s, T &n)
{
    n = decimal_to_number<T>(s);
}
//----------------------------------------------------------------------------
template<class T, class InputIterator>
inline void decimal_to_number_range(
    InputIterator begin, InputIterator end, T &n)
{
    n = decimal_to_number_range<T>(begin, end);
}
//----------------------------------------------------------------------------

#if !__cpp_lib_string_view
//----------------------------------------------------------------------------
template<class T>
__VIC_NODISCARD T decimal_to_number(const char *s)
{
    if(!s) impl::throw_null_integer();
    number_parse_result<T> r = parse_decimal<T>(s);
    switch(r.status())
    {
        case number_parse_status::ok:
            return r.value();
        case number_parse_status::invalid_number:
            if(!*s) impl::throw_empty_integer();
            else impl::throw_non_digit_char();
        case number_parse_status::unrepresentable:
            impl::throw_integer_too_long();
    }
    return T(); // UNREACHABLE! Only to suppress spurious warning
}
//----------------------------------------------------------------------------
template<class T>
inline void decimal_to_number(const char *s, T &n)
{
    n = decimal_to_number<T>(s);
}
//----------------------------------------------------------------------------
#endif

} // namespace

#endif // header guard
