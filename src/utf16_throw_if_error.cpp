//
// $Id$
//

#include<__vic/utf16/status.h>
#include<__vic/utf16/exceptions.h>
#include<__vic/error.h>
#include<__vic/string_buffer.h>

namespace __vic { namespace utf16 {

//----------------------------------------------------------------------------
bool throw_if_error(status_t st)
{
    switch(st)
    {
        case status::ok: return true;
        case status::eof: return false;
        case status::truncated_code_unit: throw truncated_code_unit();
        case status::truncated_code_point: throw truncated_code_point();
        case status::invalid_sequence: throw invalid_sequence();
    }
    // Must never happen
    throw __vic::exception(__vic::msg(64) <<
        "Unexpected utf16::status value " << static_cast<int>(st));
}
//------------------------------------------------------------------------------

}} // namespace
