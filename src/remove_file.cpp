//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/throw_errno.h>
#include<__vic/posix/error.h>
#include<unistd.h>
#include<cerrno>

namespace __vic {

//----------------------------------------------------------------------------
void remove_file(const char *path)
{
    if(::unlink(path)) throw_errno("unlink");
}
//----------------------------------------------------------------------------
bool remove_file_if_exists(const char *path)
{
    if(::unlink(path) == 0) return true;
    int err = errno;
    if(posix::is_ENOENT(err)) return false;
    throw_errno("unlink", err);
}
//----------------------------------------------------------------------------
bool remove_file_nt(const char *path) noexcept
{
    return ::unlink(path) == 0;
}
//----------------------------------------------------------------------------

} // namespace
