// UTF-8 code points writer
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2013

#ifndef __VIC_UTF8_WRITER_H
#define __VIC_UTF8_WRITER_H

#include<__vic/defs.h>
#include<__vic/unicode.h>
#include<__vic/bits.h>
#include<cstddef>

namespace __vic { namespace utf8 {

//////////////////////////////////////////////////////////////////////////////
template<class ByteWriter>
class writer
{
    ByteWriter w;
    void write_byte(unsigned char b) { w.write(b); }
    void write_bytes(const unsigned char *p, size_t len)
        { while(len--) write_byte(*p++); }
public:
    typedef ByteWriter byte_writer_type;
    ByteWriter &get_byte_writer() { return w; }
    const ByteWriter &get_byte_writer() const { return w; }

#if __cpp_variadic_templates && __cpp_rvalue_references
    template<class... Args>
    explicit writer(Args&&... args) : w(std::forward<Args>(args)...) {}
#else
    writer() {}
    explicit writer(const ByteWriter &w) : w(w) {}
#endif

    void write(unicode_t );
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class ByteWriter>
void writer<ByteWriter>::write(unicode_t cp)
{
    if(cp < 0x80) // single byte (ASCII)
        write_byte(cp); // 0xxxxxxx
    else if(cp < 0x0800) // 2 bytes
    {
        write_byte(0xC0 | (cp >> 6));   // 110xxxxx
        write_byte(0x80 | (cp & 0x3F)); // 10xxxxxx
    }
    else // more bytes
    {
        // Cases with 1 & 2 bytes can be processed here
        // They are processed specifically only for optimization reasons
        unsigned char utf8_cp[6];
        size_t len =
          //cp < 0x80      ? 1 :
          //cp < 0x0800    ? 2 :
            cp < 0x10000   ? 3 :
            cp < 0x200000  ? 4 :
            cp < 0x4000000 ? 5 :
                             6 ;
        for(int i = len - 1; i; i--, cp >>= 6)
            utf8_cp[i] = 0x80 | (cp & 0x3F); // ... | __vic::get_lsbs(cp, 6)
        utf8_cp[0] = __vic::msb_ones<unicode_t>(len) | cp; // ... | __vic::get_lsbs(cp, 7 - len)
        write_bytes(utf8_cp, len);
    }
}
//----------------------------------------------------------------------------

}} // namespace

#endif // header guard
