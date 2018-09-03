//
// $Id$
//

#include<__vic/base16.h>

namespace __vic {

//----------------------------------------------------------------------------
const char *base16::bad_length::what() const noexcept
{
    return "Bad BASE16 length";
}
//----------------------------------------------------------------------------
const char *base16::bad_digit::what() const noexcept
{
    return "Bad BASE16 digit";
}
//----------------------------------------------------------------------------

} // namespace
