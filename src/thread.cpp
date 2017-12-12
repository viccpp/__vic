//
// $Id$
//

#include<__vic/thread.h>
#include<__vic/windows/throw_last_error.h>
#include<exception>
#ifdef _MSC_VER
#include<__vic/throw_errno.h>
#include<process.h> // _beginthreadex
#endif

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
        h = o.h;
        o.h = 0;
    }
    return *this;
}
#endif
//----------------------------------------------------------------------------
void thread::start()
{
#ifdef _MSC_VER
    h = reinterpret_cast<HANDLE>(
        ::_beginthreadex(0, 0, __vic_thread_impl_func, this, 0, 0));
    if(!h) throw_errno("_beginthreadex");
#else
    h = ::CreateThread(0, 0, __vic_thread_impl_func, this, 0, 0);
    if(!h) windows::throw_last_error("CreateThread");
#endif
}
//----------------------------------------------------------------------------
void thread::cancel()
{
    if(!::TerminateThread(handle(), DWORD(-1)))
        windows::throw_last_error("TerminateThread");
    h = 0;
}
//----------------------------------------------------------------------------
void thread::join()
{
    h.Wait();
    //DWORD res;
    //if(!::GetExitCodeThread(handle(), &res))
    //    windows::throw_last_error("GetExitCodeThread");
    h.Close();
    h = 0;
}
//----------------------------------------------------------------------------
bool thread::alive() const
{
    DWORD res;
    if(!::GetExitCodeThread(handle(), &res))
        windows::throw_last_error("GetExitCodeThread");
    return res == STILL_ACTIVE;
}
//----------------------------------------------------------------------------
__VIC_THREAD_RETURNTYPE __vic_thread_impl_func(void *that)
{
    static_cast<thread *>(that)->worker();
    return 0;
}
//----------------------------------------------------------------------------

} // namespace
