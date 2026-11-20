//
// $Id$
//

#include<__vic/thread.h>
#include<__vic/windows/throw_last_error.h>
#include<exception>
#if __VIC_USE_BEGINTHREADEX
#include<__vic/throw_errno.h>
#include<process.h> // _beginthreadex
#endif

namespace __vic {

//----------------------------------------------------------------------------
thread::~thread()
{
    if(joinable())
    {
        // Should never be executed!
        // Application logic corruption
        // Attempting to destruct a thread object that was not joined
        std::terminate();
    }
}
//----------------------------------------------------------------------------
void thread::start()
{
#if __VIC_USE_BEGINTHREADEX
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
    join();
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
    return joinable() && !h.Wait(0);
}
//----------------------------------------------------------------------------
thread::id thread::get_id() const
{
    if(!joinable()) return id();
    // Requires _WIN32_WINNT >= 0x0502 // Server 2003 SP1, XP SP2
    DWORD tid = GetThreadId(h);
    if(tid == 0) windows::throw_last_error("GetThreadId");
    return id(tid);
}
//----------------------------------------------------------------------------
__VIC_THREAD_RETURNTYPE __vic_thread_impl_func(void *that)
{
    static_cast<thread *>(that)->worker();
    return 0;
}
//----------------------------------------------------------------------------

} // namespace
