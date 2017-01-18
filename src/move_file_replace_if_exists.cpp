//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/posix/error.h>
#include<__vic/throw_errno.h>
#include<cstdio>
#include<cerrno>

namespace __vic {

//----------------------------------------------------------------------------
bool move_file_replace_if_exists(const char *src_path, const char *dest_path)
{
    if(std::rename(src_path, dest_path) == 0) return true;
    switch(int err = errno)
    {
        __VIC_CASE_ENOENT // input file doesn't exist
            return false;
        case EXDEV:  // src and dest are not on the same filesystem
            if(!copy_file_if_exists(src_path, dest_path, true)) return false;
            remove_file_if_exists(src_path);
            return true;
        default:
            throw_errno("rename", err);
    }
}
//----------------------------------------------------------------------------

} // namespace
