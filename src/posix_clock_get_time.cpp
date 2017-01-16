//
// $Id$
//

#include<__vic/posix/time.h>
#include<__vic/throw_errno.h>

namespace __vic { namespace posix {

#if _POSIX_TIMERS > 0
//----------------------------------------------------------------------------
time_spec clock_base::get_time_(clockid_t id)
{
    time_spec ts;
    if(::clock_gettime(id, &ts)) throw_errno("clock_gettime");
    return ts;
}
//----------------------------------------------------------------------------
#else
//----------------------------------------------------------------------------
time_spec nanoseconds_since_epoch()
{
    ::timeval tv;
    if(::gettimeofday(&tv, nullptr)) throw_errno("gettimeofday");
    return time_spec(tv.tv_sec, tv.tv_usec * 1000L);
}
//----------------------------------------------------------------------------
#endif

}} // namespace
