// Threads support
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_THREAD_H
#define __VIC_THREAD_H

#include<__vic/defs.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// Base class for thread objects
class thread : private non_copyable
{
public:
    typedef /*TBD*/ native_handle_type;

    thread();
    virtual ~thread();

#if  __cpp_rvalue_references
    thread(thread &&o) noexcept;
    thread &operator=(thread && ) noexcept;
#endif

    class id
    {
        typedef native_handle_type id::*unspecified_bool_type;
    public:
        id();

        operator unspecified_bool_type() const;
        native_handle_type handle();

        friend bool operator==(id a, id b);
        friend bool operator!=(id a, id b);
    };

    void start();
    void cancel();
    void join();

    bool alive() const;
    bool joinable() const;

    id get_id() const;
    native_handle_type handle() const;
protected:
    virtual void worker() = 0;
};
//////////////////////////////////////////////////////////////////////////////
namespace this_thread
{
    void sleep_ms(unsigned msec);
    thread::id get_id();
}
//////////////////////////////////////////////////////////////////////////////

} // namespace

#endif // header guard
