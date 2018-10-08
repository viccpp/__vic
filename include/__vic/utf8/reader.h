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
#include<__vic/utf8/status.h>
#include<__vic/bits.h>

namespace __vic { namespace utf8 {

//////////////////////////////////////////////////////////////////////////////
template<class ByteReader>
class reader
{
    ByteReader r;
    bool read_byte(unsigned char &b) { return r.read(b); }
public:
    typedef ByteReader byte_reader_type;
    ByteReader &get_byte_reader() { return r; }
    const ByteReader &get_byte_reader() const { return r; }

#if __cpp_variadic_templates && __cpp_rvalue_references
    template<class... Args>
    explicit reader(Args&&... args) : r(std::forward<Args>(args)...) {}
#else
    reader() {}
    explicit reader(ByteReader r) : r(r) {}
#endif

    status_t parse(unicode_t & );
    bool read(unicode_t &cp) { return throw_if_error(parse(cp)); }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class ByteReader>
status_t reader<ByteReader>::parse(unicode_t &cp)
{
    unsigned char b;
    if(!read_byte(b)) return status::eof;
    // Two short paths for the most frequent cases and generic case
    if((b & 0x80) == 0) cp = b; // 0xxxxxxx - 1 byte
    else if((b & 0xE0) == 0xC0) // 110xxxxx - 2 bytes
    {
        unicode_t ch = (b & 0x1F) << 6;
        if(!read_byte(b) || !is_continuation_byte(b))
            return status::truncated_code_point;
        ch |= b & 0x3F;
        if(ch < 0x80) return status::overlong_encoding;
        cp = ch;
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
            if(!read_byte(b) || !is_continuation_byte(b))
                return status::truncated_code_point;
            ch <<= 6;
            ch |= b & 0x3F;
        }
        if(ch < length_thresholds[seqlen-2])
            return status::overlong_encoding;
        cp = ch;
    }
    else return status::no_leading_byte; // not a start byte
    return status::ok;
}
//----------------------------------------------------------------------------
template<class ByteReader>
inline reader<ByteReader> make_reader(ByteReader r)
{
    return reader<ByteReader>(r);
}
//----------------------------------------------------------------------------

}} // namespace

#endif // header guard
