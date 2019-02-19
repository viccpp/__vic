//
// $Id$
//

#include<__vic/posix/thread.h>
#include<__vic/throw_errno.h>
#include<cerrno>

namespace __vic { namespace posix {

#ifdef __VIC_POSIX_RT__
//----------------------------------------------------------------------------
bool this_thread::sigwaitinfo_at_most(
    const ::sigset_t &set, const ::timespec &timeout, ::siginfo_t &si)
{
    int sig_no = ::sigtimedwait(&set, &si, &timeout);
    if(sig_no >= 0) return true;
    switch(errno)
    {
        case EAGAIN: // timeout
        case EINTR: // interrupted by signal other than one of those in set
            return false;
        default: throw_errno("sigtimedwait");
    }
}
//----------------------------------------------------------------------------
#endif

}} // namespace
