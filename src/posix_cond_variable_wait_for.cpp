//
// $Id$
//

#include<__vic/posix/thread.h>
#include<__vic/posix/time.h>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
// Can depend on librt.a (clock_gettime) on Linux
// therefore moved to the separate file
bool cond_variable::wait_for(::pthread_mutex_t &m, unsigned long msec)
{
    return wait_until(m,
        nanoseconds_since_epoch() + time_spec(msec, time_spec::msec));
}
//----------------------------------------------------------------------------

}} // namespace
