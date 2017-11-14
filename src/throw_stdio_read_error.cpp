//
// $Id$
//

#include<__vic/stdio_file.h>
#include<__vic/throw_errno.h>

namespace __vic {

//----------------------------------------------------------------------------
void throw_stdio_read_error()
{
    throw_errno("I/O error: read failed");
}
//----------------------------------------------------------------------------

} // namespace
