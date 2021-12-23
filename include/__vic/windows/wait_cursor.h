// RAII-wrapper. Temporarily shows a wait cursor (usually an hourglass)
//
// Platform: ISO C++ 98/11 - Windows
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_WINDOWS_WAIT_CURSOR_H
#define __VIC_WINDOWS_WAIT_CURSOR_H

#include<__vic/defs.h>
#include<windows.h>

namespace __vic { namespace windows {

//////////////////////////////////////////////////////////////////////////////
class WaitCursor : private non_copyable
{
    HCURSOR old_cursor;
public:
    explicit WaitCursor(HCURSOR h) : old_cursor(::SetCursor(h)) {}
    ~WaitCursor() { ::SetCursor(old_cursor); }

    static HCURSOR GetDefault() { return ::LoadCursor(0, IDC_WAIT); }
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
