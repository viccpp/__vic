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
#include<__vic/ascii.h>
#include<exception>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
class base16
{
    template<class CharSWriter, class Func>
    static void encode_byte_(unsigned char , CharSWriter & , Func );
    template<class ByteSReader, class CharSWriter, class Func>
    static void encode_(ByteSReader & , CharSWriter & , Func );
    struct to_hex_digit_lower
    {
        char operator()(int d) const { return ascii::toxdigit_lower(d); }
    };
    struct to_hex_digit_upper
    {
        char operator()(int d) const { return ascii::toxdigit_upper(d); }
    };
public:
    __VIC_SCOPED_ENUM_BEGIN(status)
    {
        ok,
        invalid_length,
        invalid_digit
    }
    __VIC_SCOPED_ENUM_END(status)

    struct bad_format : public std::exception
    {
    };
    struct bad_length : public bad_format
    {
        const char *what() const noexcept;
    };
    struct bad_digit : public bad_format
    {
        const char *what() const noexcept;
    };

    // Byte -> Text
    template<class CharSWriter>
    static void encode_byte_lower(unsigned char , CharSWriter );
    template<class CharSWriter>
    static void encode_byte_upper(unsigned char , CharSWriter );

    // Bytes -> Text
    template<class ByteSReader, class CharSWriter>
    static void encode_lower(ByteSReader , CharSWriter );
    template<class ByteSReader, class CharSWriter>
    static void encode_upper(ByteSReader , CharSWriter );

    // Text -> Bytes
    template<class CharSReader, class ByteSWriter>
    static void decode(CharSReader , ByteSWriter );
    template<class CharSReader, class ByteSWriter>
    static status_t try_decode(CharSReader , ByteSWriter );
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class CharSWriter, class Func>
inline void base16::encode_byte_(
    unsigned char byte, CharSWriter &w, Func to_hex_digit)
{
    w.write(to_hex_digit(hi_nibble(byte)));
    w.write(to_hex_digit(lo_nibble(byte)));
}
//----------------------------------------------------------------------------
template<class ByteSReader, class CharSWriter, class Func>
inline void base16::encode_(ByteSReader &r, CharSWriter &w, Func to_hex_digit)
{
    unsigned char byte;
    while(r.read(byte))
        encode_byte_(byte, w, to_hex_digit);
}
//----------------------------------------------------------------------------
template<class CharSWriter>
void base16::encode_byte_lower(unsigned char byte, CharSWriter w)
{
    encode_byte_(byte, w, to_hex_digit_lower());
}
//----------------------------------------------------------------------------
template<class CharSWriter>
void base16::encode_byte_upper(unsigned char byte, CharSWriter w)
{
    encode_byte_(byte, w, to_hex_digit_upper());
}
//----------------------------------------------------------------------------
template<class ByteSReader, class CharSWriter>
void base16::encode_lower(ByteSReader r, CharSWriter w)
{
    encode_(r, w, to_hex_digit_lower());
}
//----------------------------------------------------------------------------
template<class ByteSReader, class CharSWriter>
void base16::encode_upper(ByteSReader r, CharSWriter w)
{
    encode_(r, w, to_hex_digit_upper());
}
//----------------------------------------------------------------------------
template<class CharSReader, class ByteSWriter>
base16::status_t base16::try_decode(CharSReader r, ByteSWriter w)
{
    bool first = true;
    int hi_part;
    char ch;
    while(r.read(ch))
    {
        int d = ascii::xdigit_to_number(ch);
        if(d < 0) return status::invalid_digit;
        if(first) hi_part = d;
        else w.write(static_cast<unsigned char>((hi_part << 4) | d));
        first = !first;
    }
    if(!first) return status::invalid_length; // the length is odd
    return status::ok;
}
//----------------------------------------------------------------------------
template<class CharSReader, class ByteSWriter>
void base16::decode(CharSReader r, ByteSWriter w)
{
    switch(base16::try_decode(__VIC_STD_MOVE(r), __VIC_STD_MOVE(w)))
    {
        case status::ok: return;
        case status::invalid_length: throw bad_length();
        case status::invalid_digit: throw bad_digit();
    }
    // UNREACHABLE
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
