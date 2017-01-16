//
// $Id$
//

#include<__vic/posix/thread.h>
#include<__vic/throw_errno.h>
#include<cerrno>

namespace __vic { namespace posix {

#ifdef __VIC_POSIX_RT__
//----------------------------------------------------------------------------
::siginfo_t this_thread::sigwaitinfo(const ::sigset_t &set)
{
    for(;;)
    {
        ::siginfo_t si;
        int sig_no = ::sigwaitinfo(&set, &si);
        if(sig_no >= 0) return si;
        if(errno != EINTR) throw_errno("sigwaitinfo");
        // Interrupted by signal. Try again
    }
}
//----------------------------------------------------------------------------
#endif

}} // namespace
