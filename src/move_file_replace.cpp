//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/throw_errno.h>
#include<cstdio>
#include<cerrno>

namespace __vic {

//----------------------------------------------------------------------------
void move_file_replace(const char *src_path, const char *dest_path)
{
    if(std::rename(src_path, dest_path) == 0) return;
    int err = errno;
    if(errno != EXDEV) throw_errno("rename", err);
    // src and dest are not on the same filesystem
    copy_file(src_path, dest_path, true);
    remove_file_if_exists(src_path);
}
//----------------------------------------------------------------------------

} // namespace
