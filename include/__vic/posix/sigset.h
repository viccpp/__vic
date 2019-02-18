// C++ wrapper for sigset_t
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_POSIX_SIGSET_H
#define __VIC_POSIX_SIGSET_H

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
    template<size_t Size> sigset(const int (&sigs)[Size])
    {
        assign(sigs, Size);
    }
#if __cpp_initializer_lists
    sigset(std::initializer_list<int> sigs)
    {
        assign(sigs.begin(), sigs.size());
    }
    sigset &operator=(std::initializer_list<int> sigs)
    {
        return assign(sigs.begin(), sigs.size());
    }
#endif

    static sigset full() { sigset s; s.fill(); return s; }
    static sigset empty() { sigset s; s.clear(); return s; }

    sigset &assign(const int *sigs, size_t n)
    {
        clear();
        while(n--) add(*sigs++);
        return *this;
    }
    template<size_t Size>
    sigset &operator=(const int (&sigs)[Size])
    {
        return assign(sigs, Size);;
    }

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

}} // namespace

#endif // header guard
