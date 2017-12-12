// Plain non-recursive mutex
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_MUTEX_H
#define __VIC_MUTEX_H

#include<__vic/defs.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
class mutex : private non_copyable
{
public:
    void lock();
    bool try_lock();
    bool unlock() noexcept;
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
