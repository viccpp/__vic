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

}} // namespace

#endif // header guard
