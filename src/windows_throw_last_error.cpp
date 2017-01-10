//
// $Id$
//

#include<__vic/windows/error.h>
#include<windows.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
void throw_last_error(const char *prompt, DWORD err_code)
{
    throw error(prompt, err_code);
}
//----------------------------------------------------------------------------
void throw_last_error(const char *prompt)
{
    throw_last_error(prompt, ::GetLastError());
}
//----------------------------------------------------------------------------

}} // namespace
