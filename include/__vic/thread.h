// Threads support
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_THREAD_H
#define __VIC_THREAD_H

#include<__vic/defs.h>
#include<pthread.h>

namespace __vic {

extern "C" void *__vic_thread_impl_func(void * );

//////////////////////////////////////////////////////////////////////////////
// Base class for thread objects
class thread : private non_copyable
{
public:
    typedef ::pthread_t native_handle_type;

    thread() {}
    virtual ~thread();

#if  __cpp_rvalue_references
    thread(thread &&o) noexcept : tid(o.tid) { o.tid = id(); }
    thread &operator=(thread && ) noexcept;
#endif

    class id
    {
        ::pthread_t tid;
        bool has_value_;
        typedef native_handle_type id::*unspecified_bool_type;
    public:
        id() : has_value_(false) {}
        explicit id(::pthread_t t) : tid(t), has_value_(true) {}

        operator unspecified_bool_type() const
            { return has_value_ ? &id::tid : 0; }
        native_handle_type handle() const { return tid; }

        friend bool operator==(id a, id b)
        {
            if(!a) return !b;
            return b && ::pthread_equal(a.tid, b.tid);
        }
        friend bool operator!=(id a, id b) { return !(a == b); }
    };

    void start();
    void cancel();
    void join();

    bool alive() const;
    bool joinable() const { return tid; }
    void kill(int );

    id get_id() const { return tid; }
    native_handle_type handle() const { return tid.handle(); }
protected:
    virtual void worker() = 0;
private:
    id tid;
    friend void *__vic_thread_impl_func(void * );
};
//////////////////////////////////////////////////////////////////////////////
namespace this_thread
{
    void sleep_ms(unsigned msec);
    inline thread::id get_id() { return thread::id(::pthread_self()); }
}
//////////////////////////////////////////////////////////////////////////////

} // namespace

#endif // header guard
