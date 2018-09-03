//
// $Id$
//

#include<__vic/base16.h>

namespace __vic {

//----------------------------------------------------------------------------
const char *base16::bad_format::what() const noexcept
{
    return "Bad HEX string";
}
//----------------------------------------------------------------------------

} // namespace
