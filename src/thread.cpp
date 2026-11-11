//
// $Id$
//

#include<__vic/thread.h>
#include<exception>

namespace __vic {

//----------------------------------------------------------------------------
thread::~thread()
{
    if(joinable())
    {
        // Should never be executed!
        // Application logic corruption
        // Attempting to destruct thread-object with still active thread
        std::terminate();
    }
}
//----------------------------------------------------------------------------

} // namespace
