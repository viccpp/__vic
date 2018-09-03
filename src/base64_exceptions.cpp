//
// $Id$
//

#include<__vic/base64.h>

namespace __vic {

//----------------------------------------------------------------------------
const char *base64::bad_format::what() const noexcept
{
    return "Bad BASE64 format";
}
//----------------------------------------------------------------------------

} // namespace
