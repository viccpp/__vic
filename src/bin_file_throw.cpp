//
// $Id$
//

#include<__vic/bin_file.h>
#include<__vic/error.h>

namespace __vic {

//----------------------------------------------------------------------------
void bin_file::throw_last_error(const char *msg)
{
    throw exception(msg);
}
//----------------------------------------------------------------------------

} // namespace
