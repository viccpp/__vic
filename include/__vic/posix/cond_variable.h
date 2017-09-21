// C++ wrapper for pthread_cond_t
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_POSIX_COND_VARIABLE_H
#define __VIC_POSIX_COND_VARIABLE_H

#include<__vic/posix/_cfg.h>
#include<__vic/defs.h>
#include<__vic/posix/mutex.h>
#include<pthread.h>

namespace __vic { namespace posix {

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

    bool wait_for(::pthread_mutex_t & , unsigned long ); // msec
    bool wait_for(mutex &m, unsigned long msec)
        { return wait_for(*m.handle(), msec); }

    void signal();
    void broadcast();

    // C++11-compatible synonyms
    void notify_one() { signal(); }
    void notify_all() { broadcast(); }
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
