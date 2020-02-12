//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/throw_errno.h>
#include<__vic/posix/error.h>
#include<cstdio>
#include<cerrno>

namespace __vic {

//----------------------------------------------------------------------------
bool rename_file_replace_if_exists(const char *src_name, const char *dest_name)
{
    if(std::rename(src_name, dest_name) == 0) return true;
    int err = errno;
    if(posix::is_ENOENT(err)) return false; // input file doesn't exist
    throw_errno("rename", err);
}
//----------------------------------------------------------------------------

} // namespace
