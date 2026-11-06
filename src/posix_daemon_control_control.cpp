//
// $Id$
//

#include<__vic/posix/daemon_control.h>
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
pid_t read_pid(const char *pid_file_name)
{
    posix::file file(pid_file_name, O_RDONLY | O_CLOEXEC);
    if(!file.is_open())
    {
        int err = errno;
        if(posix::is_ENOENT(err)) return 0; // no PID-file - not running
        throw_errno("open: PID-file", err);
    }
    char buf[32];
    size_t n = file.read_max(buf, sizeof buf);
    if(n < sizeof buf) // too long input is invalid
    {
        char *end = skip_back_if(buf, buf + n, is_ascii_ws());
        number_parse_result<pid_t> pid = parse_decimal<pid_t>(buf, end);
        if(pid && pid.value() > 0) return pid.value();
    }
    throw exception("PID-file is broken");
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
    pid_t pid = read_pid(pid_file_name);
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
            pid_t pid = read_pid(pid_file_name);
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
    pid_t pid = read_pid(pid_file_name);
    if(pid != 0) // process is running
    {
        send_signal(pid, SIGTERM); // stop the process
        while(::kill(pid, 0) == 0) // and wait for termination
            this_thread::sleep_ms(200);
    }
}
//----------------------------------------------------------------------------

}} // namespace
