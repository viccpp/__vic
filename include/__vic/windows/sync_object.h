// Base of Event, Semaphore, Mutex, etc
//
// Platform: ISO C++ 98/11 - Windows
// $Id$
//
// (c) __vic 2017

#ifndef __VIC_WINDOWS_SYNC_OBJECT_H
#define __VIC_WINDOWS_SYNC_OBJECT_H

#include<__vic/defs.h>
#include<__vic/windows/handle.h>
#include<__vic/windows/throw_last_error.h>
#if __cplusplus >= 201103L && !defined(__VIC_HAVE_STD_CHRONO)
#define __VIC_HAVE_STD_CHRONO 1
#endif
#ifdef __VIC_HAVE_STD_CHRONO
#include<chrono>
#endif

namespace __vic { namespace windows {

//////////////////////////////////////////////////////////////////////////////
class SyncObject : private non_copyable
{
    Handle h;

    template<class T>
    static DWORD ceil_(T t)
    {
        DWORD timeout = ~DWORD(0);
        return t < timeout ? static_cast<DWORD>(t) : timeout;
    }
protected:
    SyncObject(const char *err, HANDLE h) : h(h)
        { if(!h) throw_last_error(err); }
    ~SyncObject() { h.CloseNT(); }
public:
    bool Wait(DWORD timeout = INFINITE) const { return h.Wait(timeout); }
#ifdef __VIC_HAVE_STD_CHRONO
    bool wait_for(std::chrono::milliseconds ms) const { return Wait(ceil_(ms.count())); }
#endif
    HANDLE handle() const { return h; }
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
