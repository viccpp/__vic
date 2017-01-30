//
// $Id$
//

#include<__vic/io.h>
#include<__vic/throw_errno.h>

namespace __vic {

//----------------------------------------------------------------------------
void throw_stdio_write_error()
{
    throw_errno("I/O error: write failed");
}
//----------------------------------------------------------------------------

} // namespace
