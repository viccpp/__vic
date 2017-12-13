//
// $Id$
//

#include<__vic/thread.h>
#include<__vic/throw_errno.h>
#include<exception>
#include<signal.h>

namespace __vic {

//----------------------------------------------------------------------------
thread::~thread()
{
    if(joinable() && alive())
    {
        // Should never be executed!
        // Application logic corruption
        // Attempting to destruct thread-object with still active thread
        std::terminate();
    }
}
//----------------------------------------------------------------------------
#if __cpp_rvalue_references
thread &thread::operator=(thread &&o) noexcept
{
    if(&o != this)
    {
        if(joinable() && alive()) std::terminate();
        tid = o.tid;
        o.tid = id();
    }
    return *this;
}
#endif
//----------------------------------------------------------------------------
void thread::start()
{
    ::pthread_t tid;
    int err = ::pthread_create(&tid, 0, __vic_thread_impl_func, this);
    if(err) throw_errno("pthread_create", err);
    this->tid = id(tid);
}
//----------------------------------------------------------------------------
void thread::cancel()
{
    int err = ::pthread_cancel(handle());
    if(err) throw_errno("pthread_cancel", err);
}
//----------------------------------------------------------------------------
void thread::join()
{
    void *retval;
    int err = ::pthread_join(handle(), &retval);
    if(err) throw_errno("pthread_join", err);
    tid = id();
}
//----------------------------------------------------------------------------
void thread::kill(int signo)
{
    int err = ::pthread_kill(handle(), signo);
    if(err) throw_errno("pthread_kill", err);
}
//----------------------------------------------------------------------------
bool thread::alive() const
{
    // ESRCH is returned on error
    return ::pthread_kill(handle(), 0) == 0;
}
//----------------------------------------------------------------------------
void *__vic_thread_impl_func(void *that)
{
    static_cast<thread *>(that)->worker();
    return 0;
}
//----------------------------------------------------------------------------

} // namespace
