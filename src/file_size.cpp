//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/posix/file_stat.h>

namespace __vic {

//----------------------------------------------------------------------------
uintmax_t file_size(const char *path)
{
    return posix::file_stat(path).size();
}
//----------------------------------------------------------------------------

} // namespace
