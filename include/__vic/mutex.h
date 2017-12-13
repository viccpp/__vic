// Plain non-recursive mutex
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_MUTEX_H
#define __VIC_MUTEX_H

#include<__vic/defs.h>
#include<__vic/posix/mutex.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
class mutex
{
    posix::mutex m;
public:
    void lock() { m.lock(); }
    bool try_lock() { return m.try_lock(); }
    bool unlock() noexcept { m.unlock(); }
};
//////////////////////////////////////////////////////////////////////////////
class mutex_lock : private non_copyable
{
    mutex &m;
public:
    enum adopt_t { adopt };

    explicit mutex_lock(mutex &m) : m(m) { m.lock(); }
    mutex_lock(mutex &m, adopt_t) : m(m) {}
    ~mutex_lock() { m.unlock(); }
};
//////////////////////////////////////////////////////////////////////////////

} // namespace

#endif // header guard
