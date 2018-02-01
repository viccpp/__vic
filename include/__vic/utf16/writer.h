// UTF-16 code points writer
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_UTF16_WRITER_H
#define __VIC_UTF16_WRITER_H

#include<__vic/defs.h>
#include<__vic/unicode.h>
#include<__vic/utf16/defs.h>

namespace __vic { namespace utf16 {

//////////////////////////////////////////////////////////////////////////////
template<class CodeUnitWriter>
class writer
{
    CodeUnitWriter w;
    void write_unit(code_unit_t u) { w.write(u); }
public:
    typedef CodeUnitWriter code_unit_writer_type;
    CodeUnitWriter &get_code_unit_writer() { return w; }
    const CodeUnitWriter &get_code_unit_writer() const { return w; }

#if __cpp_variadic_templates && __cpp_rvalue_references
    template<class... Args>
    explicit writer(Args&&... args) : w(std::forward<Args>(args)...) {}
#else
    writer() {}
    explicit writer(const CodeUnitWriter &w) : w(w) {}
#endif

    void write(unicode_t );
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class CodeUnitWriter>
void writer<CodeUnitWriter>::write(unicode_t cp)
{
    if(cp <= 0xFFFF)
        write_unit(cp);
    else
    {
        cp -= 0x10000; // 20 bits
        write_unit(hi_surrogate_min | (cp >> 10));   // hi 10 bits: 110110xx xxxxxxxx
        write_unit(lo_surrogate_min | (cp & 0x3FF)); // lo 10 bits: 110111xx xxxxxxxx
    }
}
//----------------------------------------------------------------------------

}} // namespace

#endif // header guard
