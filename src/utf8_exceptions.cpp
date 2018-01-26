//
// $Id$
//

#include<__vic/utf8/exceptions.h>

namespace __vic { namespace utf8 {

//------------------------------------------------------------------------------
const char *no_leading_byte::what() const noexcept
{
    return "No UTF-8 leading byte found"; // unexpected continuation byte
}
//------------------------------------------------------------------------------
const char *truncated_code_point::what() const noexcept
{
    return "Truncated UTF-8 code point"; // incomplete multibyte sequence
}
//------------------------------------------------------------------------------
const char *overlong_encoding::what() const noexcept
{
    return "Overlong UTF-8 encoding";
}
//------------------------------------------------------------------------------
const char *code_point_too_big::what() const noexcept
{
    return "UTF-8 code point value is too big";
}
//------------------------------------------------------------------------------

}} // namespace
