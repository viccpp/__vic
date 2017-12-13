// Windows-like event sync object
//
// ISO C++ 98 - POSIX / ISO C++ 11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_WAITABLE_EVENT_H
#define __VIC_WAITABLE_EVENT_H

#include<__vic/defs.h>
#if __cplusplus >= 201103L // C++11
#include<mutex>
#include<condition_variable>
#include<atomic>
#include<chrono>
#else // C++98
#include<__vic/posix/mutex.h>
#include<__vic/posix/cond_variable.h>
#endif

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
class waitable_event
{
#if __cplusplus >= 201103L // C++11
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
#else // C++98
    posix::mutex mtx;
    posix::cond_variable cond;
    bool signaled_;
#endif
public:
    explicit waitable_event(bool = false);
    ~waitable_event();

    void set();
    void reset(); // clear the signaled state
    bool signaled() const;

    void wait();
    bool wait_ms(unsigned );
#if __cplusplus >= 201103L // C++11
    template<class Rep, class Period>
    bool wait_for(const std::chrono::duration<Rep,Period> & );
    template<class Clock, class Duration>
    bool wait_until(const std::chrono::time_point<Clock,Duration> & );
#endif
};
//////////////////////////////////////////////////////////////////////////////

#if __cplusplus >= 201103L // C++11
//----------------------------------------------------------------------------
inline bool waitable_event::signaled() const
{
    return signaled_.load();
}
//----------------------------------------------------------------------------
inline void waitable_event::reset()
{
    signaled_ = false;
}
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
inline bool waitable_event::wait_ms(unsigned msec)
{
    return wait_for(std::chrono::milliseconds(msec));
}
//----------------------------------------------------------------------------
#endif

} // namespace

#endif // header guard
