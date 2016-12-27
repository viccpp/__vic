//
// $Id$
//

#include<__vic/posix/thread.h>
#include<__vic/error.h>
#include<signal.h>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
int this_thread::sigwait(const ::sigset_t &set)
{
    int sig;
    if(int err = ::sigwait(&set, &sig)) throw_errno("sigwait", err);
    return sig;
}
//----------------------------------------------------------------------------

}} // namespace
