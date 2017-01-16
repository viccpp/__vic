//
// $Id$
//

#include<__vic/posix/file.h>
#include<__vic/throw_errno.h>
#include<cerrno>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
void file::write_all(int fd, const void *buf, size_t count)
{
    for(;;)
    {
        ssize_t n = ::write(fd, buf, count);
        if(n >= 0)
        {
            if(static_cast<size_t>(n) == count) return;
            // Assert: n < count
            buf = static_cast<const char *>(buf) + n;
            count -= n;
        }
        else
            if(errno != EINTR) throw_errno("write");
    }
}
//----------------------------------------------------------------------------
size_t file::write_all_nt(int fd, const void *buf, size_t count) noexcept
{
    size_t res = 0;
    for(;;)
    {
        ssize_t n = ::write(fd, buf, count);
        if(n >= 0)
        {
            res += n;
            if(static_cast<size_t>(n) == count) break;
            // Assert: n < count
            buf = static_cast<const char *>(buf) + n;
            count -= n;
        }
        else
            if(errno != EINTR) break;
    }
    return res;
}
//----------------------------------------------------------------------------

}} // namespace
