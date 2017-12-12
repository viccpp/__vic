//
// $Id$
//

#include<__vic/thread.h>
#include<exception>

namespace __vic {

//----------------------------------------------------------------------------
thread::~thread()
{
    if(joinable() && alive())
    {
        // Should never be executed!
        // Application logic corruption
        // Attempting to destruct thread-object with still active thread
        std::terminate();
    }
}
//----------------------------------------------------------------------------
#if __cpp_rvalue_references
thread &thread::operator=(thread &&o) noexcept
{
    if(&o != this)
    {
        if(joinable() && alive()) std::terminate();
        // TODO
    }
    return *this;
}
#endif
//----------------------------------------------------------------------------

} // namespace
