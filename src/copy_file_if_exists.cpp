//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/posix/error.h>
#include<__vic/throw_errno.h>
#include<__vic/posix/file.h>

namespace __vic {

void write_fd_to_file(int , const char * , bool );

//----------------------------------------------------------------------------
bool copy_file_if_exists(
    const char *src_path, const char *dest_path, bool replace)
{
    posix::file src(src_path, O_RDONLY);
    if(!src.is_open())
    {
        int err = errno;
        if(posix::is_ENOENT(err)) return false; // input file doesn't exist
        throw_errno("Cannot open input file", err);
    }
    write_fd_to_file(src.handle(), dest_path, replace);
    src.close();
    return true;
}
//----------------------------------------------------------------------------

} // namespace
