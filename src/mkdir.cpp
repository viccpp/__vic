//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/throw_errno.h>
#include<sys/stat.h>
#include<cerrno>

namespace __vic {

//----------------------------------------------------------------------------
void mkdir(const char *path, mode_t mode)
{
    if(::mkdir(path, mode)) throw_errno("mkdir");
}
//----------------------------------------------------------------------------
bool mkdir_if_absent(const char *path, mode_t mode)
{
    if(::mkdir(path, mode) == 0) return true; // Created
    int err = errno;
    if(err != EEXIST) throw_errno("mkdir", err);
    // Check whether the path is a directory
    if(!dir_exists(path)) throw_errno("mkdir_if_absent", err);
    return false; // Path exists and it's a directory
}
//----------------------------------------------------------------------------

} // namespace
