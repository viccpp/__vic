// Plain non-recursive mutex
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_MUTEX_H
#define __VIC_MUTEX_H

#include<__vic/defs.h>
#include<__vic/windows/critical_section.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
class mutex
{
    windows::CriticalSection cs;
public:
    void lock() { cs.Enter(); }
    bool try_lock() { return cs.TryEnter(); }
    bool unlock() noexcept { cs.Leave(); return true; }
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
