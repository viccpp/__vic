//
// $Id$
//

#include<__vic/windows/throw_last_error.h>
#include<__vic/windows/error.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
__VIC_NORETURN void throw_wsa_error(const char *prompt, int err_code)
{
    throw error(prompt, static_cast<DWORD>(err_code));
}
//----------------------------------------------------------------------------

}} // namespace
