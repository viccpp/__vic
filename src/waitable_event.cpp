//
// $Id$
//

#include<__vic/waitable_event.h>
#if __cplusplus < 201103L // C++98
#include<__vic/posix/time.h>
#endif

namespace __vic {

//----------------------------------------------------------------------------
waitable_event::waitable_event(bool signaled)
    : signaled_(signaled)
{
}
//----------------------------------------------------------------------------
waitable_event::~waitable_event()
{
}
//----------------------------------------------------------------------------
#if __cplusplus < 201103L // C++98
//----------------------------------------------------------------------------
bool waitable_event::signaled() const
{
    return signaled_;
}
//----------------------------------------------------------------------------
void waitable_event::reset()
{
    signaled_ = false;
}
//----------------------------------------------------------------------------
bool waitable_event::wait_ms(unsigned msec)
{
    if(signaled_) return true;
    using posix::time_spec;
    time_spec t = posix::nanoseconds_since_epoch() +
                        time_spec(msec, time_spec::msec);
    posix::mutex_lock lock(mtx);
    while(cond.wait_until(mtx, t) && !signaled_);
    return signaled_;
}
//----------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------
void waitable_event::wait()
{
    while(!signaled())
    {
#if __cplusplus >= 201103L // C++11
        std::unique_lock<std::mutex> lock(mtx);
        cond.wait(lock);
#else // C++98
        posix::mutex_lock lock(mtx);
        cond.wait(mtx);
#endif
    }
}
//----------------------------------------------------------------------------
void waitable_event::set()
{
    signaled_ = true;
    cond.notify_all();
}
//----------------------------------------------------------------------------

} // namespace
