//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/posix/file_stat.h>

namespace __vic {

//----------------------------------------------------------------------------
uint64_t file_size(const char *path)
{
    return posix::file_stat(path).size();
}
//----------------------------------------------------------------------------

} // namespace
