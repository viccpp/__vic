//
// $Id$
//

#include<__vic/windows/throw_last_error.h>
#include<winsock2.h>

namespace __vic { namespace windows {

//----------------------------------------------------------------------------
__VIC_NORETURN void throw_wsa_error(const char *prompt)
{
    // WSAGetLastError() can be used without WSAStartup()
    throw_wsa_error(prompt, ::WSAGetLastError());
}
//----------------------------------------------------------------------------

}} // namespace
