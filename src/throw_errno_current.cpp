//
// $Id$
//

#include<__vic/throw_errno.h>
#include<cerrno>

namespace __vic {

//----------------------------------------------------------------------------
void throw_errno(const char *prompt)
{
    throw_errno(prompt, errno);
}
//----------------------------------------------------------------------------

} // namespace
