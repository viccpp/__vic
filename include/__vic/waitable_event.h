// Windows-like event sync object
//
// Platform: ISO C++ 98/11 - Windows
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_WAITABLE_EVENT_H
#define __VIC_WAITABLE_EVENT_H

#include<__vic/defs.h>
#include<__vic/windows/event.h>
#ifdef __VIC_HAVE_STD_CHRONO
#include<chrono>
#endif

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
class waitable_event
{
    windows::Event ev;
public:
    explicit waitable_event(bool signaled = false)
        : ev(true, signaled) {}

    void set() { ev.Set(); }
    void reset() { ev.Reset(); }
    bool signaled() const { return ev.Wait(0); }

    void wait() { ev.Wait(); };
    bool wait_ms(unsigned msec) { return ev.Wait(msec); }
#ifdef __VIC_HAVE_STD_CHRONO
    template<class Rep, class Period>
    bool wait_for(const std::chrono::duration<Rep,Period> &t)
    {
        return ev.wait_for(t);
    }
    template<class Clock, class Duration>
    bool wait_until(const std::chrono::time_point<Clock,Duration> &t)
    {
        using clock = typename std::chrono::time_point<Clock,Duration>::clock;
        auto now = clock::now();
        return t > now ? ev.wait_for(t - now) : signaled();
    }
#endif
};
//////////////////////////////////////////////////////////////////////////////

} // namespace

#endif // header guard
