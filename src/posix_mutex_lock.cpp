//
// $Id$
//

#include<__vic/posix/thread.h>
#include<__vic/throw_errno.h>
#include<exception>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
void mutex_lock::lock()
{
    int res = ::pthread_mutex_lock(&mtx);
    if(res) throw_errno("pthread_mutex_lock", res);
}
//----------------------------------------------------------------------------
mutex_lock::~mutex_lock() __VIC_THROWS
{
    int res = ::pthread_mutex_unlock(&mtx);
    if(res && !std::uncaught_exception())
        throw_errno("pthread_mutex_unlock", res);
}
//----------------------------------------------------------------------------

}} // namespace
