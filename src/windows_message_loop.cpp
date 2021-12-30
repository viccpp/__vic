//
// $Id$
//

#include<__vic/windows/window.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
WPARAM MessageLoop(HWND hwnd)
{
    MSG msg;
    while(::GetMessage(&msg, hwnd, 0, 0))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }
    return msg.wParam;
}
//----------------------------------------------------------------------------
bool ProcessMessages(HWND hwnd)
{
    MSG msg;
    while(::PeekMessage(&msg, hwnd, 0, 0, PM_NOREMOVE))
    {
        if(!::GetMessage(&msg, hwnd, 0, 0)) return false;
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }
    return true;
}
//----------------------------------------------------------------------------

}} // namespace
