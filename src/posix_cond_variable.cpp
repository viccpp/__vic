//
// $Id$
//

#include<__vic/posix/cond_variable.h>
#include<__vic/throw_errno.h>
#include<cerrno>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
void cond_variable::wait(::pthread_mutex_t &m)
{
    int err = ::pthread_cond_wait(&cond, &m);
    if(err) throw_errno("pthread_cond_wait", err);
}
//----------------------------------------------------------------------------
bool cond_variable::wait_until(::pthread_mutex_t &m, const ::timespec &abstime)
{
    int err = ::pthread_cond_timedwait(&cond, &m, &abstime);
    switch(err)
    {
        case 0:
            return true;
        case ETIMEDOUT:
            return false;
        default:
            throw_errno("pthread_cond_timedwait", err);
    }
}
//----------------------------------------------------------------------------
void cond_variable::signal()
{
    int err = ::pthread_cond_signal(&cond);
    if(err) throw_errno("pthread_cond_signal", err);
}
//----------------------------------------------------------------------------
void cond_variable::broadcast()
{
    int err = ::pthread_cond_broadcast(&cond);
    if(err) throw_errno("pthread_cond_broadcast", err);
}
//----------------------------------------------------------------------------

}} // namespace
