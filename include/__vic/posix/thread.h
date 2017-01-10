// C++ wrapper for Pthreads-related features
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_POSIX_THREAD_H
#define __VIC_POSIX_THREAD_H

#include<__vic/posix/_cfg.h>
#include<__vic/defs.h>
#include<pthread.h>
#include<signal.h>

namespace __vic { namespace posix {

//////////////////////////////////////////////////////////////////////////////
namespace this_thread
{
    int sigwait(const ::sigset_t & );
#ifdef __VIC_POSIX_RT__
    ::siginfo_t sigwaitinfo(const ::sigset_t & );
#endif

    void change_sigmask(int , const ::sigset_t & , ::sigset_t * = nullptr);
    inline void block_signals(const ::sigset_t &mask, ::sigset_t *oldmask = nullptr)
    {
        change_sigmask(SIG_BLOCK, mask, oldmask);
    }
    inline void unblock_signals(const ::sigset_t &mask, ::sigset_t *oldmask = nullptr)
    {
        change_sigmask(SIG_UNBLOCK, mask, oldmask);
    }
    inline void set_sigmask(const ::sigset_t &mask, ::sigset_t *oldmask = nullptr)
    {
        change_sigmask(SIG_SETMASK, mask, oldmask);
    }
}
//////////////////////////////////////////////////////////////////////////////
// Plain non-recursive mutex
class mutex : private non_copyable
{
    ::pthread_mutex_t mtx
#if __cplusplus >= 201103L
         = PTHREAD_MUTEX_INITIALIZER
#endif
    ;
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
// Condition variable
class cond_variable : private non_copyable
{
    ::pthread_cond_t cond
#if __cplusplus >= 201103L
         = PTHREAD_COND_INITIALIZER
#endif
     ;
public:
#if __cplusplus >= 201103L
    constexpr cond_variable() noexcept = default;
#else
    cond_variable() { ::pthread_cond_init(&cond, nullptr); }
#endif
    ~cond_variable() { ::pthread_cond_destroy(&cond); }

    void wait(::pthread_mutex_t & );
    void wait(mutex &m) { wait(*m.handle()); }

    bool wait_until(::pthread_mutex_t & , const ::timespec & );
    bool wait_until(mutex &m, const ::timespec &abstime)
        { return wait_until(*m.handle(), abstime); }

    void signal();
    void broadcast();

    // C++11-compatible synonyms
    void notify_one() { signal(); }
    void notify_all() { broadcast(); }
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
