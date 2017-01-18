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
bool move_file_if_exists(const char *src_path, const char *dest_path)
{
    // std::rename overwrites existing entry so we don't use it
    if(::link(src_path, dest_path))
        switch(int err = errno)
        {
            __VIC_CASE_ENOENT // input file doesn't exist
                return false;
            case EXDEV: // src and dest are not on the same filesystem
                if(!copy_file_if_exists(src_path, dest_path)) return false;
                break;
            default:
                throw_errno("link", err);;
        }
    remove_file_if_exists(src_path);
    return true; // OK
}
//----------------------------------------------------------------------------

} // namespace
