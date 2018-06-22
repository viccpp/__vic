// String to number conversion utilities
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2010

#ifndef __VIC_STR2NUM_H
#define __VIC_STR2NUM_H

#include<__vic/defs.h>
#include<__vic/ascii.h>
#include<__vic/tchar.h>
#include<string>
#include<limits>
#include<cerrno>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
__VIC_SCOPED_ENUM_BEGIN(number_parse_status)
{
    ok = 0,
    invalid_number = EDOM,
    unrepresentable = ERANGE
}
__VIC_SCOPED_ENUM_END(number_parse_status)
//////////////////////////////////////////////////////////////////////////////
__VIC_CONSTEXPR_FUNC
int to_errno(number_parse_status_t s) { return static_cast<int>(s); }

namespace impl {
//////////////////////////////////////////////////////////////////////////////
template<class UInt>
class unsigned_decimal_parser
{
#if __cpp_constexpr
    static constexpr UInt
        decs = std::numeric_limits<UInt>::max() / UInt(10), // count of full decades in maximum value
        ones = std::numeric_limits<UInt>::max() % UInt(10); // count of the rest ones in maximum value
#endif
    UInt res;
    typedef number_parse_status_t status;
    typedef number_parse_status st;
public:
    template<class InputIterator>
    status parse(InputIterator begin, InputIterator end)
    {
        if(begin == end) return st::invalid_number;
#if !__cpp_constexpr
        const UInt decs = std::numeric_limits<UInt>::max() / UInt(10),
                   ones = std::numeric_limits<UInt>::max() % UInt(10);
#endif
        UInt res = 0;
        do {
            if(!ascii::isdigit(*begin)) return st::invalid_number;
            UInt dig = *begin++ - '0';
            // check if the next increment will cause overflow
            if(res > decs || (res == decs && dig > ones))
                return st::unrepresentable;
            res *= UInt(10); // decimal left shift (one digit)
            res += dig;
        } while(begin != end);
        this->res = res;
        return st::ok;
    }
    status parse(const std::string &s) { return parse(&*s.begin(), &*s.end()); }
    status parse(const char *s) { return s ? parse(s, tchar::end(s)) : st::invalid_number; }
    UInt result() const { return res; }
};
//////////////////////////////////////////////////////////////////////////////
template<class Int>
class signed_decimal_parser
{
#if __cpp_constexpr
    static constexpr Int
        decs = std::numeric_limits<Int>::max() / Int(10), // count of full decades in maximum value
        ones = std::numeric_limits<Int>::max() % Int(10); // count of the rest ones in maximum value
#endif
    Int res;
    typedef number_parse_status_t status;
    typedef number_parse_status st;
public:
    template<class InputIterator>
    status parse(InputIterator begin, InputIterator end)
    {
        if(begin == end) return st::invalid_number;
#if !__cpp_constexpr
        const Int decs = std::numeric_limits<Int>::max() / Int(10),
                  ones = std::numeric_limits<Int>::max() % Int(10);
#endif
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
            if(!ascii::isdigit(*begin)) return st::invalid_number;
            Int dig = *begin++ - '0';
            // check if the next increment will cause overflow
            if(res > decs) return st::unrepresentable;
            else if(res == decs && dig > ones)
            {
                // cut off the minimal negative case
                if(negative && dig == ones + 1 && begin == end)
                    return (this->res = std::numeric_limits<Int>::min(), st::ok);
                return st::unrepresentable;
            }
            res *= Int(10);
            res += dig;
        } while(begin != end);
        this->res = negative ? -res : res;
        return st::ok;
    }
    status parse(const std::string &s) { return parse(&*s.begin(), &*s.end()); }
    status parse(const char *s) { return s ? parse(s, tchar::end(s)) : st::invalid_number; }
    Int result() const { return res; }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
__VIC_NORETURN void throw_empty_integer();
__VIC_NORETURN void throw_null_integer();
__VIC_NORETURN void throw_non_digit_char();
__VIC_NORETURN void throw_integer_too_long();
//----------------------------------------------------------------------------
} // namespace

//////////////////////////////////////////////////////////////////////////////
template<class > struct decimal_parser; // not defined

template<> struct decimal_parser<signed char> : impl::signed_decimal_parser<signed char> {};
template<> struct decimal_parser<short> : impl::signed_decimal_parser<short> {};
template<> struct decimal_parser<int> : impl::signed_decimal_parser<int> {};
template<> struct decimal_parser<long> : impl::signed_decimal_parser<long> {};
template<> struct decimal_parser<__VIC_LONGLONG> : impl::signed_decimal_parser<__VIC_LONGLONG> {};

template<> struct decimal_parser<unsigned char> : impl::unsigned_decimal_parser<unsigned char> {};
template<> struct decimal_parser<unsigned short> : impl::unsigned_decimal_parser<unsigned short> {};
template<> struct decimal_parser<unsigned> : impl::unsigned_decimal_parser<unsigned> {};
template<> struct decimal_parser<unsigned long> : impl::unsigned_decimal_parser<unsigned long> {};
template<> struct decimal_parser<unsigned __VIC_LONGLONG> : impl::unsigned_decimal_parser<unsigned __VIC_LONGLONG> {};
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
// String to number conversion with strict format control
//----------------------------------------------------------------------------
template<class T>
T decimal_to_number(const std::string &s)
{
    decimal_parser<T> p;
    switch(p.parse(s))
    {
        case number_parse_status::ok:
            return p.result();
        case number_parse_status::invalid_number:
            if(s.empty()) impl::throw_empty_integer();
            else impl::throw_non_digit_char();
        case number_parse_status::unrepresentable:
            impl::throw_integer_too_long();
    }
    return T(); // UNREACHABLE! Only to suppress spurious warning
}
//----------------------------------------------------------------------------
template<class T>
T decimal_to_number(const char *s)
{
    if(!s) impl::throw_null_integer();
    decimal_parser<T> p;
    switch(p.parse(s))
    {
        case number_parse_status::ok:
            return p.result();
        case number_parse_status::invalid_number:
            if(!*s) impl::throw_empty_integer();
            else impl::throw_non_digit_char();
        case number_parse_status::unrepresentable:
            impl::throw_integer_too_long();
    }
    return T(); // UNREACHABLE! Only to suppress spurious warning
}
//----------------------------------------------------------------------------
template<class T, class InputIterator>
T decimal_to_number_range(InputIterator begin, InputIterator end)
{
    decimal_parser<T> p;
    switch(p.parse(begin, end))
    {
        case number_parse_status::ok:
            return p.result();
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
