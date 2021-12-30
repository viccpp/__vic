//
// $Id$
//

#include<__vic/windows/window.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
void Window::SetClientAreaSize(int width, int height)
{
    RECT r_out = GetRect();
    RECT r_in  = GetClientRect();
    int dx = r_out.right  - r_out.left - r_in.right,
        dy = r_out.bottom - r_out.top  - r_in.bottom;
    SetSize(width + dx, height + dy);
}
//----------------------------------------------------------------------------
void Window::MoveToCenter()
{
    int cx_maximized = ::GetSystemMetrics(SM_CXMAXIMIZED),
        cy_maximized = ::GetSystemMetrics(SM_CYMAXIMIZED);
    RECT r = GetRect();
    int x = (cx_maximized - (r.right - r.left)) / 2,
        y = (cy_maximized - (r.bottom - r.top)) / 2;
    MoveTo(x, y);
}
//----------------------------------------------------------------------------

}} // namespace
