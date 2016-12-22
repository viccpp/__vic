//
// $Id$
//

#include<__vic/error.h>
#include<cerrno>

namespace __vic {

//----------------------------------------------------------------------------
void throw_errno(const char *prompt, int err_no)
{
    throw libc_error(prompt, err_no);
}
//----------------------------------------------------------------------------
void throw_errno(const char *prompt)
{
    throw_errno(prompt, errno);
}
//----------------------------------------------------------------------------

} // namespace
