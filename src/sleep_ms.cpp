//
// $Id$
//

#include<__vic/thread.h>
#include<__vic/posix/time.h>
#include<__vic/throw_errno.h>
#include<cerrno>

namespace __vic {

//----------------------------------------------------------------------------
void this_thread::sleep_ms(unsigned msec)
{
    posix::time_spec req(msec, posix::time_spec::msec), res;
    errno = 0;
    while(nanosleep(&req, &res))
    {
        if(errno != EINTR
#ifdef _AIX
            && errno
#endif
        ) throw_errno("nanosleep");
        errno = 0;
        req = res;
    }
}
//----------------------------------------------------------------------------

} // namespace
