//
// $Id$
//

#include<__vic/windows/event.h>
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
Event::Event(bool bManualReset, bool bInitialSignaled, LPCSTR lpName)
:
    SyncObject("CreateEvent", ::CreateEventA(
        nullptr, bManualReset, bInitialSignaled, lpName))
{
}
//----------------------------------------------------------------------------
void Event::Set()
{
    if(!::SetEvent(handle())) throw_last_error("SetEvent");
}
//----------------------------------------------------------------------------
void Event::Reset()
{
    if(!::ResetEvent(handle())) throw_last_error("ResetEvent");
}
//----------------------------------------------------------------------------

}} // namespace
