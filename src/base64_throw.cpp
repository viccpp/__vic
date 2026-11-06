//
// $Id$
//

#include<__vic/base64.h>
#include<__vic/error.h>
#include<__vic/string_buffer.h>

namespace __vic {

//----------------------------------------------------------------------------
void base64::throw_if_error(status_t s)
{
    switch(s)
    {
        case status::ok: return;
        case status::invalid_length: throw bad_length();
        case status::invalid_digit: throw bad_digit();
        case status::invalid_padding: throw bad_padding();
    }
    // Must never happen
    throw __vic::exception(__vic::msg(64) <<
        "Unexpected base64::status value " << static_cast<int>(s));
}
//----------------------------------------------------------------------------

} // namespace
