//
// $Id$
//

#include<__vic/posix/daemon_control.h>
#include<__vic/posix/pidfile.h>
#include<__vic/posix/file.h>
#include<__vic/posix/error.h>
#include<__vic/ascii_string.h>
#include<__vic/error.h>
#include<__vic/throw_errno.h>
#include<__vic/str2num.h>
#include<__vic/string_buffer.h>
#include<__vic/posix/process.h>
#include<__vic/algorithm.h>
#include<__vic/char_predicates.h>
#include<__vic/thread.h>
#include<sys/types.h>
#include<signal.h>
#include<cstdio>
#include<cerrno>

namespace __vic { namespace posix {

namespace {
//----------------------------------------------------------------------------
pid_t read_pid(int fd)
{
    char buf[32];
    size_t n = posix::file::read_max(fd, buf, sizeof buf);
    if(n < sizeof buf) // too long input is invalid
    {
        char *end = skip_back_if(buf, buf + n, is_ascii_ws());
        number_parse_result<pid_t> pid = parse_decimal<pid_t>(buf, end);
        if(pid && pid.value() > 0) return pid.value();
    }
    throw exception("PID-file is broken");
}
//----------------------------------------------------------------------------
// Returns the PID of the running daemon or 0 if it isn't running.
// The PID-file is left open in `file`
pid_t running_pid(const char *pid_file_name, posix::file &file)
{
    if(!file.open(pid_file_name, O_RDONLY | O_CLOEXEC))
    {
        int err = errno;
        if(is_ENOENT(err)) return 0; // no PID-file
        throw_errno("open: PID-file", err);
    }
    if(!pidfile::is_locked(file.handle())) return 0; // stale PID-file
    return read_pid(file.handle());
}
//----------------------------------------------------------------------------
pid_t running_pid(const char *pid_file_name)
{
    posix::file file;
    return running_pid(pid_file_name, file);
}
//----------------------------------------------------------------------------
void send_signal(pid_t pid, int signo)
{
    if(::kill(pid, signo))
        switch(int err = errno)
        {
            case EPERM: throw exception("Insufficient privileges");
            case ESRCH: throw exception("No running process found");
            default: throw_errno("kill", err);
        }
}
//----------------------------------------------------------------------------
void send_signal(const char *pid_file_name, int signo)
{
    pid_t pid = running_pid(pid_file_name);
    if(pid == 0) throw exception("No running process found");
    send_signal(pid, signo);
}
//----------------------------------------------------------------------------
} // namespace

//----------------------------------------------------------------------------
int daemon_control::control(const char *cmd, const char *pid_file_name)
{
    if(ascii::equal_icase(cmd, "stop"))
        send_signal(pid_file_name, SIGTERM);
    else if(ascii::equal_icase(cmd, "kill"))
        send_signal(pid_file_name, SIGKILL);
    else if(ascii::equal_icase(cmd, "status")
         || ascii::equal_icase(cmd, "state"))
    {
        try
        {
            pid_t pid = running_pid(pid_file_name);
            if(pid != 0 && process_alive(pid))
                return (std::fputs("Running\n", stdout), 0);
            else
                return (std::fputs("Not running\n", stdout), 1);
        }
        catch(const std::exception &ex)
        {
            std::fprintf(stderr, "%s\n", ex.what());
        }
        return 2; // error
    }
    else throw exception(msg(64) << "Unknown command: \"" << cmd << '"');
    return 0;
}
//----------------------------------------------------------------------------
void daemon_control::stop_and_wait(const char *pid_file_name)
{
    posix::file file;
    pid_t pid = running_pid(pid_file_name, file);
    if(pid == 0) return; // not running
    send_signal(pid, SIGTERM); // stop the process
    // Wait for termination: the lock is released when the daemon exits.
    // Unlike kill(pid, 0), this cannot be fooled by PID reuse
    while(pidfile::is_locked(file.handle()))
        this_thread::sleep_ms(200);
}
//----------------------------------------------------------------------------

}} // namespace
