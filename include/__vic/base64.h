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

    static const char abc[]; // BASE64 alphabet

    // Bytes -> Text
    template<class InIter, class OutIter>
    static void encode(InIter , InIter , OutIter );

    // Text -> Bytes
    template<class InIter, class OutIter>
    static void decode(InIter , InIter , OutIter );

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
template<class InIter, class OutIter>
void base64::encode(InIter begin, InIter end, OutIter out)
{
    unsigned char triad[3];
    int pos = 0;
    for(; begin != end; ++begin)
    {
        triad[pos++] = *begin;
        if(pos == 3)
        {
            *out++ = abc[triad[0] >> 2];
            *out++ = abc[((triad[0] & 0x03) << 4) | (triad[1] >> 4)];
            *out++ = abc[((triad[1] & 0x0F) << 2) | (triad[2] >> 6)];
            *out++ = abc[triad[2] & 0x3F];
            pos = 0;
        }
    }
    if(pos > 0)
    {
        *out++ = abc[triad[0] >> 2];
        if(pos == 2)
        {
            *out++ = abc[((triad[0] & 0x03) << 4) | (triad[1] >> 4)];
            *out++ = abc[(triad[1] & 0x0F) << 2];
        }
        else // if(pos == 1)
        {
            *out++ = abc[(triad[0] & 0x03) << 4];
            *out++ = '=';
        }
        *out++ = '=';
    }
}
//----------------------------------------------------------------------------
template<class InIter, class OutIter>
void base64::decode(InIter begin, InIter end, OutIter out)
{
    char quad[4];
    unsigned char code[4];
    int pos = 0;
    for(; begin != end; ++begin)
    {
        char ch = *begin;
        if(ascii::isspace(ch)) continue; // skip whitespace
        quad[pos++] = ch;
        if(pos == 4)
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
            *out++ = (code[0] << 2) | (code[1] >> 4);
            if(code[2] != 255)
            {
                *out++ = ((code[1] & 0x0F) << 4) | (code[2] >> 2);
                if(code[3] != 255)
                    *out++ = ((code[2] & 0x03) << 6) | code[3];
            }
            pos = 0;
        }
    }
    if(pos) throw bad_format();
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
