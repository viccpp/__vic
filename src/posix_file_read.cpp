//
// $Id$
//

#include<__vic/posix/file.h>
#include<__vic/error.h>
#include<cerrno>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
size_t file::read_max(int fd, void *buf, size_t count)
{
    size_t res = 0;
    for(;;)
    {
        ssize_t n = ::read(fd, buf, count);
        if(n > 0)
        {
            res += n;
            if(static_cast<size_t>(n) == count) break;
            buf = static_cast<char *>(buf) + n;
            count -= n;
        }
        else if(n == 0) break;
        else if(errno != EINTR) throw_errno("read");
    }
    return res;
}
//----------------------------------------------------------------------------
size_t file::read_some(int fd, void *buf, size_t count)
{
    for(;;)
    {
        ssize_t n = ::read(fd, buf, count);
        if(n >= 0) return n;
        // Assert: n < 0
        if(errno != EINTR) throw_errno("read");
        // Interrupted by signal. Try again
    }
}
//----------------------------------------------------------------------------

}} // namespace
