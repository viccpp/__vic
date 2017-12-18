// Threads support
//
// Platform: ISO C++ 98/11 - Windows
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_THREAD_H
#define __VIC_THREAD_H

#include<__vic/defs.h>
#include<__vic/windows/handle.h>

namespace __vic {

#if defined(_MSC_VER) || defined(__MINGW32__)
#define __VIC_USE_BEGINTHREADEX 1
#define __VIC_THREAD_RETURNTYPE unsigned __stdcall
#else
#define __VIC_THREAD_RETURNTYPE DWORD WINAPI
#endif
// Internal implementation function
extern "C" __VIC_THREAD_RETURNTYPE __vic_thread_impl_func(void * );

//////////////////////////////////////////////////////////////////////////////
// Base class for thread objects
class thread : private non_copyable
{
public:
    typedef HANDLE native_handle_type;

    thread() : h(0) {}
    virtual ~thread();

#if  __cpp_rvalue_references
    thread(thread &&o) noexcept : h(o.h) { o.h = 0; }
    thread &operator=(thread && ) noexcept;
#endif

    class id
    {
        HANDLE h;
        typedef native_handle_type id::*unspecified_bool_type;
    public:
        explicit id(HANDLE h = 0) : h(h) {}

        operator unspecified_bool_type() const { return h ? &id::h : 0; }
        native_handle_type handle() const { return h; }

        friend bool operator==(id a, id b) { return a.h == b.h; }
        friend bool operator!=(id a, id b) { return a.h != b.h; }
    };

    void start();
    void cancel();
    void join();

    bool alive() const;
    bool joinable() const { return h; }

    id get_id() const { return id(handle()); }
    native_handle_type handle() const { return h; }
protected:
    virtual void worker() = 0;
private:
    windows::Handle h;
    friend __VIC_THREAD_RETURNTYPE __vic_thread_impl_func(void * );
};
//////////////////////////////////////////////////////////////////////////////
namespace this_thread
{
    inline void sleep_ms(unsigned msec) { ::Sleep(msec); }
    inline thread::id get_id() { return thread::id(::GetCurrentThread()); }
}
//////////////////////////////////////////////////////////////////////////////

} // namespace

#endif // header guard
