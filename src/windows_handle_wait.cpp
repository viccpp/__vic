//
// $Id$
//

#include<__vic/windows/handle.h>
#include<__vic/error.h>
#include<__vic/string_buffer.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
bool Handle::Wait(DWORD timeout)
{
    switch(DWORD res = ::WaitForSingleObject(h, timeout))
    {
        case WAIT_OBJECT_0: return true;
        case WAIT_TIMEOUT: return false;
        case WAIT_ABANDONED: throw WaitAbandoned();
        case WAIT_FAILED: throw_last_error("WaitForSingleObject");
        default: throw exception(__vic::msg(64) <<
            "WaitForSingleObject status is " << res);
    }
}
//----------------------------------------------------------------------------

}} // namespace
