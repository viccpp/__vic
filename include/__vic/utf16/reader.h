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
#include<__vic/utf16/read_result.h>

namespace __vic { namespace utf16 {

//////////////////////////////////////////////////////////////////////////////
// Desired CodeUnitReader's interface:
//
// struct CodeUnitReader
// {
//     // Expected returned .status() values: status::ok,
//     //                                     status::eof or
//     //                                     status::truncated_code_unit
//     utf16::read_unit_result operator()();
// };
//////////////////////////////////////////////////////////////////////////////
template<class CodeUnitReader>
class reader
{
    CodeUnitReader r;
    read_unit_result read_unit() { return r(); }
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

    read_result parse();
    sread_result<unicode_t> read() { return convert_or_throw(parse()); }
    sread_result<unicode_t> operator()() { return read(); }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
template<class CodeUnitReader>
read_result reader<CodeUnitReader>::parse()
{
    read_unit_result rr = read_unit();
    if(!rr) return rr.status();
    code_unit_t c16 = rr.value();
    if(c16 < hi_surrogate_min || c16 > lo_surrogate_max) return c16;
    else if((c16 & 0xFC00) == hi_surrogate_min) // 110110xx xxxxxxxx
    {
        unicode_t c32 = c16 & 0x3FF;
        c32 <<= 10;
        rr = read_unit();
        switch(rr.status())
        {
            case status::ok: break;
            case status::eof: return status::truncated_code_point;
            default: return rr.status();
        }
        c16 = rr.value();
        if((c16 & 0xFC00) == lo_surrogate_min) // 110111xx xxxxxxxx
            return (c32 | (c16 & 0x3FF)) + 0x10000;
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
