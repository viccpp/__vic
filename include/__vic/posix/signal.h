// Signal-related stuff
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_POSIX_SIGNAL_H
#define __VIC_POSIX_SIGNAL_H

#include<__vic/defs.h>
#include<signal.h>
#if __cpp_initializer_lists
#include<initializer_list>
#endif

namespace __vic { namespace posix {

//////////////////////////////////////////////////////////////////////////////
class sigset
{
    ::sigset_t set;
public:
    sigset() __VIC_DEFAULT_CTR // uninitialized!
    sigset(const ::sigset_t &s) : set(s) {}
#if __cpp_initializer_lists
    sigset(std::initializer_list<int> sigs)
    {
        clear();
        for(int signo : sigs) add(signo);
    }
#endif

    static sigset full() { sigset s; s.fill(); return s; }
    static sigset empty() { sigset s; s.clear(); return s; }

    sigset &add(int signo) { ::sigaddset(&set, signo); return *this; }
    sigset &del(int signo) { ::sigdelset(&set, signo); return *this; }
    sigset &operator+=(int signo) { return add(signo); }
    sigset &operator-=(int signo) { return del(signo); }
    sigset &operator<<(int signo) { return add(signo); }
    sigset &operator>>(int signo) { return del(signo); }

    sigset &fill() { ::sigfillset(&set); return *this; }
    sigset &clear() { ::sigemptyset(&set); return *this; }

    bool is_member(int signo) const { return ::sigismember(&set, signo) == 1; }
    bool contains(int signo) const { return is_member(signo); }

    operator ::sigset_t &() { return set; }
    operator const ::sigset_t &() const { return set; }

    ::sigset_t *operator&() { return &set; }
    const ::sigset_t *operator&() const { return &set; }
};
//////////////////////////////////////////////////////////////////////////////

void ignore_signals(const int [], size_t );
//----------------------------------------------------------------------------
template<size_t Size>
inline void ignore_signals(const int (&sigs)[Size])
{
    ignore_signals(sigs, Size);
}
//----------------------------------------------------------------------------
#if __cpp_initializer_lists
inline void ignore_signals(std::initializer_list<int> sigs)
{
    ignore_signals(sigs.begin(), sigs.size());
}
#endif
//----------------------------------------------------------------------------

}} // namespace

#endif // header guard
