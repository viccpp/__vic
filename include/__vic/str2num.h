// String to number conversion utilities
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2010

#ifndef __VIC_STR2NUM_H
#define __VIC_STR2NUM_H

#include<__vic/defs.h>
#include<__vic/meta.h>
#include<__vic/ascii.h>
#include<cstring>
#include<string>
#include<limits>

namespace __vic {

namespace impl {
//----------------------------------------------------------------------------
__VIC_NORETURN void throw_empty_integer();
__VIC_NORETURN void throw_null_integer();
__VIC_NORETURN void throw_non_digit_char();
__VIC_NORETURN void throw_integer_too_long();
//----------------------------------------------------------------------------
template<class UInt, class InputIterator>
inline UInt decimal_to_uinteger(InputIterator begin, InputIterator end)
{
    static __VIC_CONSTEXPR_VAR UInt
        decs = std::numeric_limits<UInt>::max() / UInt(10), // count of full decades in maximum value
        ones = std::numeric_limits<UInt>::max() % UInt(10); // count of the rest ones in maximum value
    if(begin == end) throw_empty_integer();
    UInt res = 0;
    do {
        if(!ascii::isdigit(*begin)) throw_non_digit_char();
        UInt dig = *begin++ - '0';
        // check if the next increment will cause owerflow
        if(res > decs || (res == decs && dig > ones))
            throw_integer_too_long();
        res *= UInt(10); // decimal left shift (one digit)
        res += dig;
    } while(begin != end);
    return res;
}
//----------------------------------------------------------------------------
template<class Int, class InputIterator>
inline Int decimal_to_integer(InputIterator begin, InputIterator end)
{
    static __VIC_CONSTEXPR_VAR Int
        decs = std::numeric_limits<Int>::max() / Int(10), // count of full decades in maximum value
        ones = std::numeric_limits<Int>::max() % Int(10); // count of the rest ones in maximum value
    if(begin == end) throw_empty_integer();
    bool negative = false;
    switch(*begin)
    {
        case '-':
            negative = true;
            // no break, fall through
        case '+':
            ++begin;
    }
    Int res = 0;
    do {
        if(!ascii::isdigit(*begin)) throw_non_digit_char();
        Int dig = *begin++ - '0';
        // check if the next increment will cause owerflow
        if(res > decs) throw_integer_too_long();
        else if(res == decs && dig > ones)
        {
            // cut off the minimal negative case
            if(negative && dig == ones + 1 && begin == end)
                return std::numeric_limits<Int>::min();
            throw_integer_too_long();
        }
        res *= Int(10);
        res += dig;
    } while(begin != end);
    return negative ? -res : res;
}
//----------------------------------------------------------------------------
} // namespace

//----------------------------------------------------------------------------
// String to number conversion with strict format control
//----------------------------------------------------------------------------
template<class T>
typename enable_if<is_signed_integer<T>::value, T>::type
    decimal_to_number(const std::string &s)
{
    return impl::decimal_to_integer<T>(s.begin(), s.end());
}
//----------------------------------------------------------------------------
template<class T>
typename enable_if<is_unsigned_integer<T>::value, T>::type
    decimal_to_number(const std::string &s)
{
    return impl::decimal_to_uinteger<T>(s.begin(), s.end());
}
//----------------------------------------------------------------------------
template<class T>
typename enable_if<is_signed_integer<T>::value, T>::type
    decimal_to_number(const char *s)
{
    if(!s) impl::throw_null_integer();
    const char *end = std::strchr(s, 0); // tchar::end(s)
    return impl::decimal_to_integer<T>(s, end);
}
//----------------------------------------------------------------------------
template<class T>
typename enable_if<is_unsigned_integer<T>::value, T>::type
    decimal_to_number(const char *s)
{
    if(!s) impl::throw_null_integer();
    const char *end = std::strchr(s, 0); // tchar::end(s)
    return impl::decimal_to_uinteger<T>(s, end);
}
//----------------------------------------------------------------------------
template<class T, class InputIterator>
typename enable_if<is_signed_integer<T>::value, T>::type
    decimal_to_number_range(InputIterator begin, InputIterator end)
{
    return impl::decimal_to_integer<T>(begin, end);
}
//----------------------------------------------------------------------------
template<class T, class InputIterator>
typename enable_if<is_unsigned_integer<T>::value, T>::type
    decimal_to_number_range(InputIterator begin, InputIterator end)
{
    return impl::decimal_to_uinteger<T>(begin, end);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// The same functions with the result as 2nd out argument
template<class T>
inline void decimal_to_number(const std::string &s, T &n)
{
    n = decimal_to_number<T>(s);
}
//----------------------------------------------------------------------------
template<class T>
inline void decimal_to_number(const char *s, T &n)
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

} // namespace

#endif // header guard
