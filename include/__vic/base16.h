// Base16 encoder/decoder
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2016

#ifndef __VIC_BASE16_H
#define __VIC_BASE16_H

#include<__vic/defs.h>
#include<__vic/bits.h>
#include<exception>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
class base16
{
    template<class InIter, class OutIter, class Func>
    static void encode_(InIter , InIter , OutIter , Func );
    struct to_hex_digit_lower
    {
        char operator()(int d) const { return __vic::to_hex_digit_lower(d); }
    };
    struct to_hex_digit_upper
    {
        char operator()(int d) const { return __vic::to_hex_digit_upper(d); }
    };
public:
    struct bad_format : public std::exception
    {
        const char *what() const noexcept;
    };

    // Bytes -> Text
    template<class InIter, class OutIter>
    static void encode_lower(InIter , InIter , OutIter );
    template<class InIter, class OutIter>
    static void encode_upper(InIter , InIter , OutIter );

    // Text -> Bytes
    template<class InIter, class OutIter>
    static void decode(InIter , InIter , OutIter );
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class InIter, class OutIter, class Func>
inline void base16::encode_(
    InIter begin, InIter end, OutIter out, Func to_hex_digit)
{
    for(; begin != end; ++begin)
    {
        uint8_t b = *begin;
        *out++ = to_hex_digit(hi_nibble(b));
        *out++ = to_hex_digit(lo_nibble(b));
    }
}
//----------------------------------------------------------------------------
template<class InIter, class OutIter>
void base16::encode_lower(InIter begin, InIter end, OutIter out)
{
    encode_(begin, end, out, to_hex_digit_lower());
}
//----------------------------------------------------------------------------
template<class InIter, class OutIter>
void base16::encode_upper(InIter begin, InIter end, OutIter out)
{
    encode_(begin, end, out, to_hex_digit_upper());
}
//----------------------------------------------------------------------------
template<class InIter, class OutIter>
void base16::decode(InIter begin, InIter end, OutIter out)
{
    bool first = true;
    int hi_part;
    for(; begin != end; ++begin)
    {
        int d = hex_to_number(*begin);
        if(d < 0) throw bad_format();
        if(first) hi_part = d;
        else *out++ = uint8_t((hi_part << 4) | d);
        first = !first;
    }
    if(!first) throw bad_format(); // the length if odd
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
