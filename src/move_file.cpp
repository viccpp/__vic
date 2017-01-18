//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/throw_errno.h>
#include<unistd.h>
#include<cerrno>

namespace __vic {

//----------------------------------------------------------------------------
void move_file(const char *src_path, const char *dest_path)
{
    // std::rename overwrites existing entry so we don't use it
    if(::link(src_path, dest_path))
    {
        int err = errno;
        if(err != EXDEV) throw_errno("link", err);
        // src and dest are not on the same filesystem
        copy_file(src_path, dest_path);
    }
    remove_file_if_exists(src_path);
}
//----------------------------------------------------------------------------

} // namespace
