//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/posix/error.h>
#include<__vic/throw_errno.h>
#include<unistd.h>
#include<cerrno>

namespace __vic {

//----------------------------------------------------------------------------
void rmdir(const char *path)
{
    if(::rmdir(path)) throw_errno("rmdir");
}
//----------------------------------------------------------------------------
bool rmdir_if_exists(const char *path)
{
    if(::rmdir(path) == 0) return true; // removed
    int err = errno;
    if(posix::is_ENOENT(err)) return false;
    throw_errno("rmdir", err);
}
//----------------------------------------------------------------------------

} // namespace
