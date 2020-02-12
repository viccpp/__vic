//
// $Id$
//

#include<__vic/posix/process.h>
#include<__vic/throw_errno.h>
#include<signal.h>
#include<cerrno>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
bool process_alive(pid_t pid)
{
    if(::kill(pid, 0) == 0) return true;
    switch(int err = errno)
    {
        case EPERM: return true;
        case ESRCH: return false;
        default: throw_errno("kill", err);
    }
}
//----------------------------------------------------------------------------

}} // namespace
