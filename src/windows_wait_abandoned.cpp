//
// $Id$
//

#include<__vic/windows/handle.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
const char *WaitAbandoned::what() const noexcept
{
    return "WAIT_ABANDONED";
}
//----------------------------------------------------------------------------

}} // namespace
