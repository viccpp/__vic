// UTF-16 code points reader
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_UTF16_READER_H
#define __VIC_UTF16_READER_H

#include<__vic/defs.h>
#include<__vic/unicode.h>
#include<__vic/utf16/defs.h>
#include<__vic/utf16/status.h>

namespace __vic { namespace utf16 {

//////////////////////////////////////////////////////////////////////////////
// Desired CodeUnitReader's interface:
//
// struct CodeUnitReader
// {
//     // Returns status::ok, status::eof or status::truncated_code_unit
//     status_t read_unit(code_unit_t & );
// };
//////////////////////////////////////////////////////////////////////////////
template<class CodeUnitReader>
class reader
{
    CodeUnitReader r;
    status_t read_unit(code_unit_t &u) { return r.read_unit(u); }
public:
    typedef CodeUnitReader code_unit_reader_type;
    CodeUnitReader &get_code_unit_reader() { return r; }
    const CodeUnitReader &get_code_unit_reader() const { return r; }

#if __cpp_variadic_templates && __cpp_rvalue_references
    template<class... Args>
    explicit reader(Args&&... args) : r(std::forward<Args>(args)...) {}
#else
    reader() {}
    explicit reader(CodeUnitReader r) : r(r) {}
#endif

    status_t parse(unicode_t & );
    bool read(unicode_t &cp) { return throw_if_error(parse(cp)); }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class CodeUnitReader>
status_t reader<CodeUnitReader>::parse(unicode_t &cp)
{
    code_unit_t c16;
    status_t st;
    if((st = read_unit(c16)) != status::ok) return st;
    if(c16 < hi_surrogate_min || c16 > lo_surrogate_max)
    {
        cp = c16;
        return status::ok;
    }
    else if((c16 & 0xFC00) == hi_surrogate_min) // 110110xx xxxxxxxx
    {
        unicode_t c32 = c16 & 0x3FF;
        c32 <<= 10;
        switch(st = read_unit(c16))
        {
            case status::ok: break;
            case status::eof: return status::truncated_code_point;
            default: return st;
        }
        if((c16 & 0xFC00) == lo_surrogate_min) // 110111xx xxxxxxxx
        {
            cp = (c32 | (c16 & 0x3FF)) + 0x10000;
            return status::ok;
        }
    }
    return status::invalid_sequence;
}
//----------------------------------------------------------------------------
template<class CodeUnitReader>
inline reader<CodeUnitReader> make_reader(CodeUnitReader r)
{
    return reader<CodeUnitReader>(r);
}
//----------------------------------------------------------------------------

}} // namespace

#endif // header guard
