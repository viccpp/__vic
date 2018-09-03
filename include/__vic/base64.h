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
    struct bad_format : public std::exception
    {
        const char *what() const noexcept;
    };

    static const char abc[65]; // BASE64 alphabet + null terminator

    // Bytes -> Text
    template<class ByteReader, class CharWriter>
    static void encode(ByteReader , CharWriter );

    // Text -> Bytes
    template<class CharReader, class ByteWriter>
    static void decode(CharReader , ByteWriter );

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
void base64::decode(CharReader r, ByteWriter w)
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
                    const char *p = std::strchr(abc, quad[i]);
                    if(!p) throw bad_format(); // not BASE64 char
                    code[i] = p - abc;
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
    if(pos) throw bad_format();
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
