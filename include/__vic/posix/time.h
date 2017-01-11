// POSIX time-related utilities
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$

#ifndef __VIC_POSIX_TIME_H
#define __VIC_POSIX_TIME_H

#include<__vic/posix/_cfg.h>
#include<__vic/defs.h>
#include<time.h>
#if __cplusplus >= 201103L && !defined(__VIC_HAVE_STD_CHRONO)
#define __VIC_HAVE_STD_CHRONO 1
#endif
#ifdef __VIC_HAVE_STD_CHRONO
#include<chrono>
#endif

namespace __vic { namespace posix {

using ::time_t;

//////////////////////////////////////////////////////////////////////////////
struct time_spec : ::timespec
{
    // Unit tags
    enum sec_units { sec };
    enum msec_units { msec };
    enum mksec_units { mksec };
    enum nsec_units { nsec };

    time_spec() __VIC_DEFAULT_CTR
    time_spec(time_t secs, long nsecs) { tv_sec = secs; tv_nsec = nsecs; }

    time_spec(time_t secs, sec_units)
    {
        tv_sec = secs;
        tv_nsec = 0;
    }
    time_spec(time_t msecs, msec_units)
    {
        tv_sec = msecs / 1000;
        tv_nsec = msecs % 1000 * 1000000L;
    }
    time_spec(time_t mksecs, mksec_units)
    {
        tv_sec = mksecs / 1000000UL;
        tv_nsec = mksecs % 1000000UL * 1000000L;
    }
    time_spec(time_t nsecs, nsec_units)
    {
        tv_sec = nsecs / 1000000000UL;
        tv_nsec = nsecs % 1000000000UL;
    }
#ifdef __VIC_HAVE_STD_CHRONO
    template<class Rep, class Period>
    time_spec(const std::chrono::duration<Rep,Period> &d)
    {
        auto sec = std::chrono::duration_cast<std::chrono::seconds>(d);
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(d - sec);
        tv_sec = sec.count();
        tv_nsec = ns.count();
    }
    time_spec(const std::chrono::seconds &secs)
        : time_spec(secs.count(), sec) {}
    time_spec(const std::chrono::nanoseconds &nsecs)
        : time_spec(nsecs.count(), nsec) {}

    operator std::chrono::nanoseconds() const
    {
        return std::chrono::nanoseconds(tv_nsec +
            std::chrono::nanoseconds::rep(tv_sec) * 1000000000UL);
    }

    template<class Rep, class Period>
    time_spec &operator+=(const std::chrono::duration<Rep,Period> &d)
    {
        auto sec = std::chrono::duration_cast<std::chrono::seconds>(d);
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(d - sec);
        tv_sec += sec;
        tv_nsec += ns;
        normalize_big();
        return *this;
    }
    template<class Rep, class Period>
    time_spec &operator-=(const std::chrono::duration<Rep,Period> &d)
    {
        auto sec = std::chrono::duration_cast<std::chrono::seconds>(d);
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(d - sec);
        tv_sec -= sec;
        tv_nsec -= ns;
        normalize_small();
        return *this;
    }
    time_spec &operator+=(const std::chrono::seconds &secs)
    {
        tv_sec += secs.count();
        return *this;
    }
    time_spec &operator-=(const std::chrono::seconds &secs)
    {
        tv_sec -= secs.count();
        return *this;
    }
#endif

    time_spec &operator+=(const time_spec &t)
    {
        tv_sec += t.tv_sec;
        tv_nsec += t.tv_nsec;
        normalize_big();
        return *this;
    }
    time_spec &operator-=(const time_spec &t)
    {
        tv_sec -= t.tv_sec;
        tv_nsec -= t.tv_nsec;
        normalize_small();
        return *this;
    }
private:
    void normalize_big()
    { if(tv_nsec >= 1000000000L) { tv_sec++; tv_nsec -= 1000000000L; } }
    void normalize_small()
    { if(tv_nsec < 0L) { tv_sec--; tv_nsec += 1000000000L; } }
};
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
inline bool operator==(const time_spec &t1, const time_spec &t2)
{
    return t1.tv_sec == t2.tv_sec && t1.tv_nsec == t2.tv_nsec;
}
//----------------------------------------------------------------------------
inline bool operator!=(const time_spec &t1, const time_spec &t2)
{
    return !(t1 == t2);
}
//----------------------------------------------------------------------------
inline bool operator<(const time_spec &t1, const time_spec &t2)
{
    return t1.tv_sec < t2.tv_sec ||
        (t1.tv_sec == t2.tv_sec && t1.tv_nsec < t2.tv_nsec);
}
//----------------------------------------------------------------------------
inline bool operator>(const time_spec &t1, const time_spec &t2)
{
    return t1.tv_sec > t2.tv_sec ||
        (t1.tv_sec == t2.tv_sec && t1.tv_nsec > t2.tv_nsec);
}
//----------------------------------------------------------------------------
inline bool operator<=(const time_spec &t1, const time_spec &t2)
{
    return t1.tv_sec < t2.tv_sec ||
        (t1.tv_sec == t2.tv_sec && t1.tv_nsec <= t2.tv_nsec);
}
//----------------------------------------------------------------------------
inline bool operator>=(const time_spec &t1, const time_spec &t2)
{
    return t1.tv_sec > t2.tv_sec ||
        (t1.tv_sec == t2.tv_sec && t1.tv_nsec >= t2.tv_nsec);
}
//----------------------------------------------------------------------------
inline time_spec operator+(time_spec t1, const time_spec &t2)
{
    return t1 += t2;
}
//----------------------------------------------------------------------------
inline time_spec operator-(time_spec t1, const time_spec &t2)
{
    return t1 -= t2;
}
//----------------------------------------------------------------------------

#if _POSIX_TIMERS > 0

using ::clockid_t;
template<clockid_t > struct clock; // not implemented
//////////////////////////////////////////////////////////////////////////////
struct clock_base // internal implementation type
{
#ifdef __VIC_HAVE_STD_CHRONO
    using duration = std::chrono::nanoseconds;
    using period = duration::period;
    using rep = duration::rep;
#endif
protected:
    static time_spec get_time_(clockid_t );
};
//////////////////////////////////////////////////////////////////////////////
template<clockid_t ClockID, bool Steady = false>
struct clock_impl : public clock_base // internal implementation type
{
    static __VIC_CONSTEXPR_VAR clockid_t id = ClockID;
    static __VIC_CONSTEXPR_VAR bool is_steady = Steady;
#ifdef __VIC_HAVE_STD_CHRONO
    using time_point = std::chrono::time_point<clock<ClockID>, duration>;
    static time_point now() { return time_point(get_time()); }
#endif
    static time_spec get_time() { return get_time_(id); }
};
//////////////////////////////////////////////////////////////////////////////
template<> struct clock<CLOCK_REALTIME> : clock_impl<CLOCK_REALTIME> {};
typedef clock<CLOCK_REALTIME> realtime_clock;

#ifdef _POSIX_MONOTONIC_CLOCK
template<> struct clock<CLOCK_MONOTONIC> : clock_impl<CLOCK_MONOTONIC, true> {};
typedef clock<CLOCK_MONOTONIC> monotonic_clock;
#endif
//////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
inline time_spec nanoseconds_since_epoch()
{
    return realtime_clock::get_time();
}
//----------------------------------------------------------------------------

#else

time_spec nanoseconds_since_epoch();

#endif // _POSIX_TIMERS

}} // namespace

#endif // header guard
