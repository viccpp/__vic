//
// $Id$
//

#include<__vic/io.h>
#include<__vic/throw_errno.h>

namespace __vic {

//----------------------------------------------------------------------------
void throw_stdio_read_error()
{
    throw_errno("I/O error: read failed");
}
//----------------------------------------------------------------------------

} // namespace
