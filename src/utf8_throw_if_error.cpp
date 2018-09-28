//
// $Id$
//

#include<__vic/utf8/status.h>
#include<__vic/utf8/exceptions.h>
#include<__vic/error.h>
#include<__vic/string_buffer.h>

namespace __vic { namespace utf8 {

//----------------------------------------------------------------------------
bool throw_if_error(status_t st)
{
    switch(st)
    {
        case status::ok: return true;
        case status::eof: return false;
        case status::no_leading_byte: throw no_leading_byte();
        case status::truncated_code_point: throw truncated_code_point();
        case status::overlong_encoding: throw overlong_encoding();
        case status::code_point_too_big: throw code_point_too_big();
    }
    // Must never happen
    throw __vic::exception(__vic::msg(64) <<
        "Unexpected utf8::status value " << static_cast<int>(st));
}
//------------------------------------------------------------------------------

}} // namespace
