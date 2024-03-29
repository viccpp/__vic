//
// $Id$
//

#include<__vic/throw_errno.h>
#include<__vic/error.h>

namespace __vic {

//----------------------------------------------------------------------------
void throw_errno(const char *prompt, int err_no)
{
    throw libc_error(prompt, err_no);
}
//----------------------------------------------------------------------------

} // namespace
