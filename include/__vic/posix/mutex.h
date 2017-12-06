// C++ wrapper for pthread_mutex_t
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_POSIX_MUTEX_H
#define __VIC_POSIX_MUTEX_H

#include<__vic/posix/_cfg.h>
#include<__vic/defs.h>
#include<pthread.h>

namespace __vic { namespace posix {

//////////////////////////////////////////////////////////////////////////////
// Plain non-recursive mutex
class mutex
{
    ::pthread_mutex_t mtx
#if __cplusplus >= 201103L
         = PTHREAD_MUTEX_INITIALIZER
#endif
    ;
#if __cplusplus < 201103L
    mutex(const mutex & ); // not implemeted
    mutex &operator=(const mutex & ); // not implemeted
#else
public:
    mutex(const mutex & ) = delete;
    mutex &operator=(const mutex & ) = delete;
#endif
public:
#if __cplusplus >= 201103L
    constexpr mutex() noexcept = default;
#else // C++98
    mutex() { ::pthread_mutex_init(&mtx, nullptr); }
#endif
    ~mutex() { ::pthread_mutex_destroy(&mtx); }

    void lock();
    bool try_lock();
    bool unlock() noexcept { return ::pthread_mutex_unlock(&mtx) == 0; }

    // System-specific handle
    ::pthread_mutex_t *handle() { return &mtx; }
    const ::pthread_mutex_t *handle() const { return &mtx; }
};
//////////////////////////////////////////////////////////////////////////////
// Lock-guard for mutexes
class mutex_lock : private non_copyable, private non_heap_allocatable
{
    ::pthread_mutex_t &mtx;
    void lock();
public:
    enum adopt_t { adopt };

    explicit mutex_lock(mutex &m) : mtx(*m.handle()) { lock(); }
    // avoid lock() call in constructor (for already locked mutex)
    mutex_lock(mutex &m, adopt_t) : mtx(*m.handle()) {}

    // Same constructors for Pthreads mutex
    explicit mutex_lock(::pthread_mutex_t &m) : mtx(m) { lock(); }
    mutex_lock(::pthread_mutex_t &m, adopt_t) : mtx(m) {}

    ~mutex_lock() __VIC_THROWS; // No free store allocation!
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
