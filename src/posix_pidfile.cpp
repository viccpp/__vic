//
// $Id$
//

#include<__vic/posix/pidfile.h>
#include<__vic/posix/file.h>
#include<__vic/throw_errno.h>
#include<__vic/to_text.h>
#include<cerrno>
#include<unistd.h>
#include<fcntl.h>
#if !defined(__hpux) && !defined(_AIX) && !defined(__sun)
#define HAVE_FLOCK 1
#endif
#ifdef HAVE_FLOCK
#include<sys/file.h>
#endif

namespace __vic { namespace posix {

namespace {
//----------------------------------------------------------------------------
bool lock_exclusively(int fd)
{
    errno = 0;
#ifdef HAVE_FLOCK
    if(flock(fd, LOCK_EX | LOCK_NB))
    {
        int err = errno;
        if(err == EWOULDBLOCK) return false;
        throw_errno("flock: PID-file", err);
    }
#else
    struct flock lck;
    lck.l_type = F_WRLCK;
    lck.l_whence = SEEK_SET;
    lck.l_start = lck.l_len = 0;
    if(fcntl(fd, F_SETLK, &lck) == -1)
    {
        int err = errno;
        if(err == EACCES || err == EAGAIN) return false;
        throw_errno("fcntl(F_SETLK): PID-file", err);
    }
#endif
    return true;
}
//----------------------------------------------------------------------------
// A function similar to FreeBSD's flopen()
int flcreate(const char *fname)
{
    errno = 0;
    int fd = open(fname, O_CREAT | O_EXCL | O_WRONLY, 0644);
    if(fd == -1)
    {
        int err = errno;
        if(err != EEXIST) throw_errno("open: PID-file", err);
        errno = 0;
        fd = open(fname, O_CREAT | O_WRONLY, 0644);
        if(fd == -1) throw_errno("open: PID-file");
    }
    if(!lock_exclusively(fd)) return -1;
    return fd;
}
//----------------------------------------------------------------------------
void write_pid(int fd)
{
    std::string st;
    to_text_append(getpid(), st);
    // !! may be not available on several UNICES
    if(ftruncate(fd, 0)) throw_errno("ftruncate: PID-file");
    if(lseek(fd, 0, SEEK_SET) != 0) throw_errno("lseek: PID-file");
    posix::file::write_all(fd, st.data(), st.length());
    if(fsync(fd)) throw_errno("fsync: PID-file");
}
//----------------------------------------------------------------------------
} // namespace

//----------------------------------------------------------------------------
pidfile::pidfile(std::string fname) : name(__VIC_STD_MOVE(fname)), fd(-1)
{
}
//----------------------------------------------------------------------------
pidfile::~pidfile()
{
    if(fd != -1) ::unlink(name.c_str());
}
//----------------------------------------------------------------------------
void pidfile::create()
{
    if(fd != -1) return;
    if((fd = flcreate(name.c_str())) == -1) throw already_exists();
    write_pid(fd);
}
//----------------------------------------------------------------------------
void pidfile::prepare_to_daemon()
{
#ifndef HAVE_FLOCK
    if(fd != -1) { close(fd); fd = -1; }
#endif
}
//----------------------------------------------------------------------------
void pidfile::rewrite_pid()
{
#ifndef HAVE_FLOCK
    fd = open(name.c_str(), O_CREAT | O_WRONLY, 0644);
    // Reacquire lock
    if(fd == -1 || !lock_exclusively(fd))
        throw_errno("Reacquire PID-file lock failed");
#endif
    write_pid(fd);
}
//----------------------------------------------------------------------------
const char *pidfile::already_exists::what() const noexcept
{
    return "PID-file already exists";
}
//----------------------------------------------------------------------------

}} // namespace
