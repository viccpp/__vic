//
// $Id$
//

#include<__vic/stdio_file.h>
#include<__vic/throw_errno.h>

namespace __vic {

//----------------------------------------------------------------------------
void throw_stdio_write_error()
{
    throw_errno("I/O error: write failed");
}
//----------------------------------------------------------------------------

} // namespace
