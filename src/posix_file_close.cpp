//
// $Id$
//

#include<__vic/posix/file.h>
#include<__vic/throw_errno.h>
#include<cerrno>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
void file::close_reset(int &fd)
{
#ifdef __hpux
    for(;;)
    {
        if(::close(fd) == 0) { fd = -1; return; }
        if(errno != EINTR)
        {
            // We can't call close() again in case of EIO because of
            // "the state of fildes is unspecified" according to POSIX
            fd = -1;
            throw_errno("close");
        }
        // Interrupted by signal. Try again
    }
#else
    int st = ::close(fd);
    fd = -1;
    if(st == 0) return;
    if(errno != EINTR) throw_errno("close");
#endif
}
//----------------------------------------------------------------------------
bool file::close_nt(int fd) noexcept
{
    // POSIX says that on error the state of fd is unspecified,
    // even in case of EINTR
#ifdef __hpux
    // Looks like HP-UX is the only OS who made sane behaviour here
    for(;;)
    {
        if(::close(fd) == 0) return true;
        if(errno != EINTR) return false;
        // Interrupted by signal. Try again
    }
#else
    // Other OSes including Linux, AIX, *BSD close the fd anyway, even in
    // case of EINTR, so repeat call will cause EBADF
    return ::close(fd) == 0; //?? || errno == EINTR;
#endif
}
//----------------------------------------------------------------------------

}} // namespace
