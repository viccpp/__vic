//
// $Id$
//

#if __cplusplus >= 201103L // C++11

#include<__vic/waitable_event.h>

namespace __vic {

//----------------------------------------------------------------------------
waitable_event::waitable_event(bool signaled)
    : signaled_(signaled)
{
}
//----------------------------------------------------------------------------
waitable_event::~waitable_event()
{
}
//----------------------------------------------------------------------------
void waitable_event::wait()
{
    while(!signaled())
    {
        std::unique_lock<std::mutex> lock(mtx);
        cond.wait(lock);
    }
}
//----------------------------------------------------------------------------
void waitable_event::set()
{
    signaled_ = true;
    cond.notify_all();
}
//----------------------------------------------------------------------------

} // namespace

#endif // C++11
