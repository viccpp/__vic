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
    posix::mutex_lock _(mtx);
    return signaled_;
}
//----------------------------------------------------------------------------
void waitable_event::reset()
{
    posix::mutex_lock _(mtx);
    signaled_ = false;
}
//----------------------------------------------------------------------------
bool waitable_event::wait_ms(unsigned msec)
{
    using posix::time_spec;
    time_spec t = posix::nanoseconds_since_epoch() +
                        time_spec(msec, time_spec::msec);
    posix::mutex_lock lock(mtx);
    while(!signaled_ && cond.wait_until(mtx, t));
    return signaled_;
}
//----------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------
void waitable_event::wait()
{
#if __cplusplus >= 201103L // C++11
    if(signaled()) return;
    std::unique_lock<std::mutex> lock(mtx);
    auto &s = signaled_;
    cond.wait(lock, [&s]{ return s.load(); });
#else // C++98
    posix::mutex_lock lock(mtx);
    while(!signaled_) cond.wait(mtx);
#endif
}
//----------------------------------------------------------------------------
void waitable_event::set()
{
    {
#if __cplusplus >= 201103L // C++11
        std::lock_guard<std::mutex> _(mtx);
#else // C++98
        posix::mutex_lock _(mtx);
#endif
        signaled_ = true;
    }
    cond.notify_all();
}
//----------------------------------------------------------------------------

} // namespace
