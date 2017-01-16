//
// $Id$
//

#include<__vic/posix/thread.h>
#include<__vic/throw_errno.h>
#include<signal.h>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
void this_thread::change_sigmask(int how, const sigset_t &mask, sigset_t *oldmask)
{
    int err = ::pthread_sigmask(how, &mask, oldmask);
    if(err) throw_errno("pthread_sigmask", err);
}
//----------------------------------------------------------------------------

}} // namespace
