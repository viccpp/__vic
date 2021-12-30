//
// $Id$
//

#include<__vic/windows/window.h>
#include<__vic/windows/wchar.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
int MsgBox(HWND hwnd, const char *msg, const char *title, int t)
{
    wstring wmsg = utf8to16(msg);
    //if(title && *title) return MessageBox(hwnd,
    //    static_cast<const wchar_t *>(wmsg), utf8to16(title), f);
    return MsgBox(hwnd,
        static_cast<const wchar_t *>(wmsg),
        static_cast<const wchar_t *>(title && *title ? utf8to16(title) : L""),
        t);
}
//----------------------------------------------------------------------------

}} // namespace
