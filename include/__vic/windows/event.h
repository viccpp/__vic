// C++ wrapper for Win32 API Event Object
//
// Platform: ISO C++ 98/11 - Windows
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_WINDOWS_EVENT_H
#define __VIC_WINDOWS_EVENT_H

#include<__vic/defs.h>
#include<__vic/windows/sync_object.h>

namespace __vic { namespace windows {

//////////////////////////////////////////////////////////////////////////////
class Event : public SyncObject
{
public:
    explicit Event(bool bManualReset,
         bool bInitialSignaled = false, LPCSTR lpName = nullptr);

    void Set();
    void Reset();
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
