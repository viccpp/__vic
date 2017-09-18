//
// $Id$
//

#include<__vic/stdio_file.h>
#include<__vic/error.h>

namespace __vic {

//----------------------------------------------------------------------------
void throw_stdio_read_error()
{
    throw exception("I/O error: read failed");
}
//----------------------------------------------------------------------------

} // namespace
