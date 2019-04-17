#include<__vic/posix/daemon_control.h>
#include<iostream>
#include<exception>
#include<cstring>
#include<cassert>
#include<csignal>
#include<unistd.h>
#include<sys/wait.h>

namespace tests {

static const char * const pid_file_name = "daemon_control.pid";
using __vic::posix::daemon_control;

volatile std::sig_atomic_t finish = 0;
extern "C" void sigterm_handler(int ) { finish = 1; }

void daemon_app()
{
    daemon_control app(pid_file_name);
    app.daemonize();
    std::signal(SIGTERM, sigterm_handler);
    try {
        daemon_control app(pid_file_name);
        assert(false);
    } catch(const daemon_control::already_running &) {
        // Ok
    }
    while(!finish) ::pause();
}
void control_app(pid_t child_pid)
{
    std::cout << "Starting child process..." << std::endl;
    ::sleep(1);
    assert(daemon_control::control("status", pid_file_name) == 0);
    daemon_control::stop_and_wait(pid_file_name);
    assert(daemon_control::control("status", pid_file_name) == 1);
    int st;
    assert(::waitpid(child_pid, &st, WNOHANG) > 0);
    try {
        daemon_control app(pid_file_name);
        assert(daemon_control::control("status", pid_file_name) == 0);
    } catch(const daemon_control::already_running &) {
        assert(false);
    }
    assert(daemon_control::control("status", pid_file_name) == 1);
    std::cout << "Done\n";
}
void run()
{
    switch(pid_t pid = ::fork())
    {
        case 0: // child
            daemon_app();
            return;
        case -1:
            assert(false);
        default: // parent
            control_app(pid);
    }
}

} // namespace

int main(int argc, char *argv[])
{
    try
    {
        if(argc == 2 && std::strcmp(argv[1], "interactive") == 0)
            tests::run();
        return 0;
    }
    catch(const std::exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 1;
}
