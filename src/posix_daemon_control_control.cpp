//
// $Id$
//

#include<__vic/posix/daemon_control.h>
#include<__vic/ascii_string.h>
#include<__vic/stdio_file.h>
#include<__vic/error.h>
#include<__vic/throw_errno.h>
#include<__vic/string_buffer.h>
#include<__vic/posix/process.h>
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
    stdio_file file(pid_file_name, "r");
    if(!file.is_open()) return 0;
    unsigned pid;
    if(std::fscanf(file, "%u", &pid) != 1)
         throw exception("PID-file is broken");
    return pid;
}
//----------------------------------------------------------------------------
void send_signal(pid_t pid, int signo)
{
    if(::kill(pid, signo))
        switch(errno)
        {
            case EPERM: throw exception("Insufficient privileges");
            case ESRCH: throw exception("No running process found");
            default: throw_errno("kill");
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
