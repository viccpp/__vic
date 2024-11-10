//
// $Id$
//

#include<__vic/utf16/read_result.h>
#include<__vic/utf16/exceptions.h>
#include<__vic/error.h>
#include<__vic/string_buffer.h>

namespace __vic { namespace utf16 {

//----------------------------------------------------------------------------
sread_result<unicode_t> convert_or_throw(read_result r)
{
    switch(r.status())
    {
        case status::ok: return r.value();
        case status::eof: return sread_eof;
        case status::truncated_code_unit: throw truncated_code_unit();
        case status::truncated_code_point: throw truncated_code_point();
        case status::invalid_sequence: throw invalid_sequence();
    }
    // Must never happen
    throw __vic::exception(__vic::msg(64) <<
        "Unexpected utf16::status value " << static_cast<int>(r.status()));
}
//------------------------------------------------------------------------------

}} // namespace
