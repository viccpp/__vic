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
    template<class ByteReader, class CharWriter, class Func>
    static void encode_(ByteReader & , CharWriter & , Func );
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
    template<class ByteReader, class CharWriter>
    static void encode_lower(ByteReader , CharWriter );
    template<class ByteReader, class CharWriter>
    static void encode_upper(ByteReader , CharWriter );

    // Text -> Bytes
    template<class CharReader, class ByteWriter>
    static void decode(CharReader , ByteWriter );
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class ByteReader, class CharWriter, class Func>
inline void base16::encode_(ByteReader &r, CharWriter &w, Func to_hex_digit)
{
    unsigned char byte;
    while(r.read(byte))
    {
        w.write(to_hex_digit(hi_nibble(byte)));
        w.write(to_hex_digit(lo_nibble(byte)));
    }
}
//----------------------------------------------------------------------------
template<class ByteReader, class CharWriter>
void base16::encode_lower(ByteReader r, CharWriter w)
{
    encode_(r, w, to_hex_digit_lower());
}
//----------------------------------------------------------------------------
template<class ByteReader, class CharWriter>
void base16::encode_upper(ByteReader r, CharWriter w)
{
    encode_(r, w, to_hex_digit_upper());
}
//----------------------------------------------------------------------------
template<class CharReader, class ByteWriter>
void base16::decode(CharReader r, ByteWriter w)
{
    bool first = true;
    int hi_part;
    char ch;
    while(r.read(ch))
    {
        int d = hex_to_number(ch);
        if(d < 0) throw bad_format();
        if(first) hi_part = d;
        else w.write(static_cast<unsigned char>((hi_part << 4) | d));
        first = !first;
    }
    if(!first) throw bad_format(); // the length is odd
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
