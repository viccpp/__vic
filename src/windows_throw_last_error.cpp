//
// $Id$
//

#include<__vic/windows/throw_last_error.h>
#include<__vic/windows/error.h>
#include<windows.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
void throw_last_error(const char *prompt, unsigned err_code)
{
    typedef char assert_[sizeof err_code >= sizeof(DWORD) ? 1 : -1];
    throw error(prompt, err_code);
}
//----------------------------------------------------------------------------
void throw_last_error(const char *prompt)
{
    throw_last_error(prompt, ::GetLastError());
}
//----------------------------------------------------------------------------

}} // namespace
