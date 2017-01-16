//
// $Id$
//

#include<__vic/posix/file_stat.h>
#include<__vic/string_buffer.h>
#include<__vic/throw_errno.h>
#include<__vic/posix/error.h>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
bool file_stat::get_if_exists(const char *path)
{
    if(this->try_get(path)) return true;
    int err = errno;
    if(is_ENOENT(err)) return false;
    throw_errno(__vic::msg(64) << "Can't stat file \"" << path << '"', err);
}
//----------------------------------------------------------------------------

}} // namespace
