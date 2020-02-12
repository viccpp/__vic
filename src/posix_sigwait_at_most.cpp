//
// $Id$
//

#include<__vic/posix/thread.h>
#include<__vic/throw_errno.h>
#include<__vic/error.h>
#include<signal.h>

namespace __vic { namespace posix {

#ifdef __VIC_POSIX_RT__
//----------------------------------------------------------------------------
int this_thread::sigwait_at_most(
    const ::sigset_t &set, const ::timespec &timeout)
{
    int sig_no = ::sigtimedwait(&set, nullptr, &timeout);
    if(sig_no > 0) return sig_no;
    if(sig_no == 0) throw exception("sigtimedwait returned 0");
    switch(int err = errno)
    {
        case EAGAIN: // timeout
        case EINTR: // interrupted by signal other than one of those in set
            return 0;
        default: throw_errno("sigtimedwait", err);
    }
}
//----------------------------------------------------------------------------
#endif

}} // namespace
