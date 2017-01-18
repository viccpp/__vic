//
// $Id$
//

#include<__vic/fs.h>
#include<__vic/posix/file_stat.h>
#include<__vic/posix/error.h>
#include<__vic/string_buffer.h>
#include<__vic/throw_errno.h>
#include<cerrno>

namespace __vic {

namespace {
//----------------------------------------------------------------------------
bool get_stat(const char *path, posix::file_stat &s, const char *what)
{
    if(s.try_get(path)) return true;
    int err = errno;
    switch(err)
    {
        __VIC_CASE_ENOENT
        case ENOTDIR:
            return false; // path doesn't exist
    }
    throw_errno(__vic::msg(64) <<
        "Can't stat " << what << " \"" << path << '"', err);
}
//----------------------------------------------------------------------------
} // namespace
//----------------------------------------------------------------------------
bool path_exists(const char *path)
{
    posix::file_stat s;
    return get_stat(path,s,"path");
}
//----------------------------------------------------------------------------
bool file_exists(const char *path)
{
    posix::file_stat s;
    return get_stat(path,s,"file") && s.is_regular();
}
//----------------------------------------------------------------------------
bool dir_exists(const char *path)
{
    posix::file_stat s;
    return get_stat(path,s,"dir") && s.is_dir();
}
//----------------------------------------------------------------------------

} // namespace
