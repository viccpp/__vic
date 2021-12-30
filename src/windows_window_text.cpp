//
// $Id$
//

#include<__vic/windows/window.h>
#include<__vic/windows/wchar.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
void Window::SetText(const char *st)
{
    SetText(utf8to16(st));
}
//----------------------------------------------------------------------------

}} // namespace
