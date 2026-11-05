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
    if(signaled()) return;
    std::unique_lock<std::mutex> lock(mtx);
    auto &s = signaled_;
    cond.wait(lock, [&s]{ return s.load(); });
}
//----------------------------------------------------------------------------
void waitable_event::set()
{
    {
        std::lock_guard<std::mutex> _(mtx);
        signaled_ = true;
    }
    cond.notify_all();
}
//----------------------------------------------------------------------------

} // namespace

#endif // C++11
