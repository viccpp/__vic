//
// $Id$
//

#include<__vic/posix/thread.h>
#include<__vic/throw_errno.h>
#include<cerrno>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
void mutex::lock()
{
    int res = ::pthread_mutex_lock(&mtx);
    if(res) throw_errno("pthread_mutex_lock", res);
}
//----------------------------------------------------------------------------
bool mutex::try_lock()
{
    int res = ::pthread_mutex_trylock(&mtx);
    if(res == EBUSY) return false;
    if(res) throw_errno("pthread_mutex_trylock", res);
    return true;
}
//----------------------------------------------------------------------------

}} // namespace
