//
// $Id$
//

#include<__vic/base64.h>

namespace __vic {

//----------------------------------------------------------------------------
const char *base64::bad_length::what() const noexcept
{
    return "Bad BASE64 length";
}
//----------------------------------------------------------------------------
const char *base64::bad_digit::what() const noexcept
{
    return "Bad BASE64 digit";
}
//----------------------------------------------------------------------------

} // namespace
