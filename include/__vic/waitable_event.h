// Windows-like event sync object
//
// Platform: ISO C++ 11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_WAITABLE_EVENT_H
#define __VIC_WAITABLE_EVENT_H

#include<__vic/defs.h>
#include<mutex>
#include<condition_variable>
#include<atomic>
#include<chrono>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
class waitable_event
{
    std::mutex mtx;
    std::condition_variable cond;
    class atomic_bool
    {
        std::atomic<bool> v;
    public:
        explicit atomic_bool(bool val) : v(val) {}
        void operator=(bool val) { v.store(val, std::memory_order_release); }
        bool load() const { return v.load(std::memory_order_acquire); }
    } signaled_;
public:
    explicit waitable_event(bool = false);
    ~waitable_event();

    void set();
    void reset() { signaled_ = false; } // clear the signaled state
    bool signaled() const { return signaled_.load(); }

    void wait();
    template<class Rep, class Period>
    bool wait_for(const std::chrono::duration<Rep,Period> & );
    template<class Clock, class Duration>
    bool wait_until(const std::chrono::time_point<Clock,Duration> & );
};
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
template<class R, class P>
bool waitable_event::wait_for(const std::chrono::duration<R,P> &t)
{
    if(signaled()) return true;
    std::unique_lock<std::mutex> lock(mtx);
    auto &s = signaled_;
    return cond.wait_for(lock, t, [&s]{ return s.load(); });
}
//----------------------------------------------------------------------------
template<class C, class D>
bool waitable_event::wait_until(const std::chrono::time_point<C,D> &t)
{
    if(signaled()) return true;
    std::unique_lock<std::mutex> lock(mtx);
    auto &s = signaled_;
    return cond.wait_until(lock, t, [&s]{ return s.load(); });
}
//----------------------------------------------------------------------------

} // namespace

#endif // header guard
