// Base64 encoder/decoder
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2008

#ifndef __VIC_BASE64_H
#define __VIC_BASE64_H

#include<__vic/defs.h>
#include<__vic/ascii.h>
#include<exception>
#include<cstring>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
struct base64
{
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

    static const char abc[64]; // BASE64 alphabet

    // Bytes -> Text
    template<class ByteReader, class CharWriter>
    static void encode(ByteReader , CharWriter );

    // Text -> Bytes
    template<class CharReader, class ByteWriter>
    static void decode(CharReader , ByteWriter );
    template<class CharReader, class ByteWriter>
    static status_t try_decode(CharReader , ByteWriter );

    static __VIC_CONSTEXPR_FUNC size_t encoded_length(size_t orig_len)
    {
        return (orig_len + 2) / 3 * 4; // ceil(orig_len / 3.0) * 4
    }
    static __VIC_CONSTEXPR_FUNC size_t max_decoded_length(size_t orig_len)
    {
        // TODO: the actual value depends on trailing '='
        return orig_len / 4 * 3;
    }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class ByteReader, class CharWriter>
void base64::encode(ByteReader r, CharWriter w)
{
    unsigned char triad[3];
    int pos = 0;
    while(r.read(triad[pos]))
    {
        if(pos == 2)
        {
            w.write(abc[triad[0] >> 2]);
            w.write(abc[((triad[0] & 0x03) << 4) | (triad[1] >> 4)]);
            w.write(abc[((triad[1] & 0x0F) << 2) | (triad[2] >> 6)]);
            w.write(abc[triad[2] & 0x3F]);
            pos = 0;
        }
        else pos++;
    }
    if(pos > 0)
    {
        w.write(abc[triad[0] >> 2]);
        if(pos == 2)
        {
            w.write(abc[((triad[0] & 0x03) << 4) | (triad[1] >> 4)]);
            w.write(abc[(triad[1] & 0x0F) << 2]);
        }
        else // if(pos == 1)
        {
            w.write(abc[(triad[0] & 0x03) << 4]);
            w.write('=');
        }
        w.write('=');
    }
}
//----------------------------------------------------------------------------
template<class CharReader, class ByteWriter>
base64::status_t base64::try_decode(CharReader r, ByteWriter w)
{
    char quad[4];
    unsigned char code[4];
    int pos = 0;
    char ch;
    while(r.read(ch))
    {
        if(ascii::isspace(ch)) continue; // skip whitespace
        quad[pos] = ch;
        if(pos == 3)
        {
            for(int i=0; i<4; i++)
            {
                if(quad[i] != '=')
                {
                    const char *p = static_cast<const char *>(
                        std::memchr(abc, quad[i], sizeof abc));
                    if(!p) return status::invalid_digit;
                    code[i] = static_cast<unsigned char>(p - abc);
                }
                else code[i] = 255;
            }
            w.write((code[0] << 2) | (code[1] >> 4));
            if(code[2] != 255)
            {
                w.write(((code[1] & 0x0F) << 4) | (code[2] >> 2));
                if(code[3] != 255)
                    w.write(((code[2] & 0x03) << 6) | code[3]);
            }
            pos = 0;
        }
        else pos++;
    }
    if(pos) return status::invalid_length;
    return status::ok;
}
//----------------------------------------------------------------------------
template<class CharReader, class ByteWriter>
void base64::decode(CharReader r, ByteWriter w)
{
    switch(base64::try_decode(__VIC_STD_MOVE(r), __VIC_STD_MOVE(w)))
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
