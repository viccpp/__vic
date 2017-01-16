//
// $Id$
//

#include<__vic/posix/iov.h>
#include<__vic/throw_errno.h>
#include<cassert>
#include<cerrno>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
void writev_all(int fd, ::iovec *v, unsigned v_len, size_t total_bytes)
{
    assert(total_bytes == total(v, v_len));
    for(;;)
    {
        ssize_t n = ::writev(fd, v, v_len);
        if(n < 0)
        {
            if(errno != EINTR) throw_errno("writev");
            // Interrupted by signal. Nothing was written. Try againg
        }
        else // n >= 0
        {
            if(static_cast<size_t>(n) == total_bytes) break; // all done
            cut_prefix(v, v_len, n);
        }
    }
}
//----------------------------------------------------------------------------

}} // namespace
