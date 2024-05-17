//
// $Id$
//

#include<__vic/windows/window.h>
#include<__vic/windows/wchar.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
int MsgBox(HWND hwnd, const char *msg, const char *title, int t)
{
    return MsgBox(hwnd, utf8to16(msg).c_str(),
                    title && *title ? utf8to16(title).c_str() : L"", t);
}
//----------------------------------------------------------------------------

}} // namespace
