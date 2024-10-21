// UTF-8 code points reader
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2013

#ifndef __VIC_UTF8_READER_H
#define __VIC_UTF8_READER_H

#include<__vic/defs.h>
#include<__vic/unicode.h>
#include<__vic/utf8/defs.h>
#include<__vic/utf8/read_result.h>
#include<__vic/bits.h>

namespace __vic { namespace utf8 {

//////////////////////////////////////////////////////////////////////////////
template<class ByteSReader>
class reader
{
    ByteSReader r;
    sread_result<unsigned char> read_byte() { return r(); }
public:
    typedef ByteSReader byte_reader_type;
    ByteSReader &get_byte_reader() { return r; }
    const ByteSReader &get_byte_reader() const { return r; }

#if __cpp_variadic_templates && __cpp_rvalue_references
    template<class... Args>
    explicit reader(Args&&... args) : r(std::forward<Args>(args)...) {}
#else
    reader() {}
    explicit reader(ByteSReader r) : r(r) {}
#endif

    read_result parse();
    sread_result<unicode_t> read() { return convert_or_throw(parse()); }
    sread_result<unicode_t> operator()() { return read(); }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class ByteSReader>
read_result reader<ByteSReader>::parse()
{
    sread_result<unsigned char> rr = read_byte();
    if(!rr) return status::eof;
    unsigned char b = rr.value();
    // Two short paths for the most frequent cases and generic case
    if((b & 0x80) == 0) return b; // 0xxxxxxx - 1 byte
    else if((b & 0xE0) == 0xC0) // 110xxxxx - 2 bytes
    {
        unicode_t ch = (b & 0x1F) << 6;
        rr = read_byte();
        if(!rr || !is_continuation_byte(rr.value()))
            return status::truncated_code_point;
        ch |= rr.value() & 0x3F;
        if(ch < 0x80) return status::overlong_encoding;
        return ch;
    }
    else if((b & 0xE0) == 0xE0  // 111zzzzx - 3 or more bytes
         && (b & 0x1E) != 0x1E) // at least one z is 0
    {
        unsigned seqlen = 3;
        for(unsigned char mask = 0x10; b & mask; mask >>= 1)
            seqlen++; // count leading 1-bits
        if(seqlen > 4) return status::code_point_too_big;
        // bits from the starting byte
        unicode_t ch = __vic::get_lsbs(b, 7 - seqlen);
        for(int i = seqlen; --i;) // continuation bytes
        {
            rr = read_byte();
            if(!rr || !is_continuation_byte(rr.value()))
                return status::truncated_code_point;
            ch <<= 6;
            ch |= rr.value() & 0x3F;
        }
        if(ch < length_thresholds[seqlen-2])
            return status::overlong_encoding;
        return ch;
    }
    else return status::no_leading_byte; // not a start byte
}
//----------------------------------------------------------------------------
template<class ByteSReader>
inline reader<ByteSReader> make_reader(ByteSReader r)
{
    return reader<ByteSReader>(r);
}
//----------------------------------------------------------------------------

}} // namespace

#endif // header guard
