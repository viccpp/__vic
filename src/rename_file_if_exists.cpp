//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/throw_errno.h>
#include<__vic/posix/error.h>
#include<unistd.h>
#include<cerrno>

//----------------------------------------------------------------------------
bool __vic::rename_file_if_exists(const char *src_name, const char *dest_name)
{
    // std::rename overwrites existing entry so we don't use it
    if(::link(src_name, dest_name) == 0)
    {
        if(::unlink(src_name) == 0 || posix::is_ENOENT(errno)) return true; // OK
        // Trying to remove newly created link
        int err = errno; // save errno
        ::unlink(dest_name);
        errno = err; // restore
    }
    else if(posix::is_ENOENT(errno)) // input file doesn't exist
        return false;
    throw_errno("__vic::rename_file");
}
//----------------------------------------------------------------------------
