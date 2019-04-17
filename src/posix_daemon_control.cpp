//
// $Id$
//

#include<__vic/posix/daemon_control.h>
#include<__vic/posix/process.h>

namespace __vic { namespace posix {

//----------------------------------------------------------------------------
daemon_control::daemon_control(std::string pid_file_name)
    : pid_file(__VIC_STD_MOVE(pid_file_name))
{
    try
    {
        pid_file.create();
    }
    catch(const pidfile::already_exists &)
    {
        throw already_running();
    }
}
//----------------------------------------------------------------------------
void daemon_control::daemonize()
{
    pid_file.prepare_to_daemon();
    posix::daemon(true);
    pid_file.rewrite_pid();
}
//----------------------------------------------------------------------------
const char *daemon_control::already_running::what() const noexcept
{
    return "PID-file already exists. Stop (Another instance is running?)";
}
//----------------------------------------------------------------------------

}} // namespace
