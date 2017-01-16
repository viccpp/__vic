//
// $Id$
//

#include<__vic/posix/process.h>
#include<__vic/throw_errno.h>
#include<sys/fcntl.h>
#include<unistd.h>
#include<stdlib.h> // BSD

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
void daemon(bool nochdir, bool noclose)
{
#if defined(__linux__) || \
    defined(__FreeBSD__) || \
    defined(__QNX__)
    // Redirect to the system call
    if(::daemon(nochdir, noclose)) throw_errno("daemon");
#else
    // Use own implementation
    switch(fork())
    {
        case -1: throw_errno("fork");
        case  0: break;
        default: _exit(0); // parent exit
    }
    setsid();
    if(!nochdir) chdir("/");
    if(!noclose)
    {
        int fd = open("/dev/null", O_RDWR | O_NOCTTY);
        struct fd_closer : private non_copyable
        {
            int fd;
            explicit fd_closer(int fd) : fd(fd) {}
            ~fd_closer() { if(fd > 2) close(fd); }
        } closer(fd);
        if(fd == -1
            || dup2(fd, 0) == -1
            || dup2(fd, 1) == -1
            || dup2(fd, 2) == -1
        ) throw_errno("daemon: redirection to /dev/null failed");
    }
#endif
}
//----------------------------------------------------------------------------

}} // namespace
