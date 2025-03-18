// Bytes value parser: 1K, 2M, etc
//
// Platform: ISO C++ 98
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_CONFIG_VALUES_BYTES_H
#define __VIC_CONFIG_VALUES_BYTES_H

#include<__vic/config/value.h>
#include<__vic/str2num.h>

namespace __vic { namespace config {

//////////////////////////////////////////////////////////////////////////////
template<class TUInt>
class bytes_value_parser
{
#if __cpp_static_assert
    static_assert(TUInt(-1) > TUInt(0),
                      "Only unsigned integers are supported");
#endif
    template<class Iter>
    static bool to_number_(Iter begin, Iter end, TUInt &v)
    {
        number_parse_result<TUInt> r = parse_decimal<TUInt>(begin, end);
        if(!r) return false;
        v = r.value();
        return true;
    }
public:
    static bool parse(const std::string & , TUInt & );
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class TUInt>
bool bytes_value_parser<TUInt>::parse(const std::string &s, TUInt &res)
{
    if(s.empty()) return false;
    unsigned shift;
    switch(*s.rbegin())
    {
        // Implementation note: for unsigned integral types
        // multiplication by 2^n is equivalent to bitwise
        // left shift to n bits (^ - is power not XOR!)
        case 'K': // 2^10
            shift = 10;
            break;
        case 'M': // 2^20
            shift = 20;
            break;
        case 'G': // 2^30
            shift = 30;
            break;
        default:
            return to_number_(s.begin(), s.end(), res);
    }
    // Assert: shift is set correctly
    if(shift > sizeof(TUInt)*8) return false; // type is too small. Overflow
    // Assert: shift <= sizeof(TUInt)*8
    TUInt v;
    if(!to_number_(s.begin(), s.end() - 1, v)) return false;

    // Check for overflow possibility
    // Significant non-zero bits must not be lost during shifting!
    // mask is a value with all high-order bits == 1 (111...00)
    // The length of 1-bits sequence == shift
    TUInt mask = ~TUInt(0) << (sizeof(TUInt)*8 - shift);
    if(v & mask) return false; // overflow

    res = v << shift;
    return true;
}
//----------------------------------------------------------------------------

}} // namespace

#endif // header guard
