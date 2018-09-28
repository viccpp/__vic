//
// $Id$
//

#include<__vic/utf16/exceptions.h>

namespace __vic { namespace utf16 {

//------------------------------------------------------------------------------
const char *truncated_code_unit::what() const noexcept
{
    return "Truncated UTF-16 code unit";
}
//------------------------------------------------------------------------------
const char *truncated_code_point::what() const noexcept
{
    return "Truncated UTF-16 code point";
}
//------------------------------------------------------------------------------
const char *invalid_sequence::what() const noexcept
{
    return "Invalid UTF-16 encoding";
}
//------------------------------------------------------------------------------

}} // namespace
