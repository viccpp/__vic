#ifndef __VIC_USE_MODULES
#include<__vic/posix/daemon_control.h>
#include<__vic/posix/file.h>
#include<iostream>
#include<exception>
#include<cstring>
#include<csignal>
#endif
#include<cassert>
#include<signal.h>
#include<sys/wait.h>
#include<unistd.h>
#ifdef __VIC_USE_MODULES
import std;
import __vic;
#endif

namespace tests {

static const char * const pid_file_name = "daemon_control.pid";
using __vic::posix::daemon_control;

volatile std::sig_atomic_t finish = 0;
extern "C" void sigterm_handler(int ) { finish = 1; }

void write_file(const char *filename, const char *content)
{
    assert(content);
    __vic::posix::file file(filename, O_CREAT | O_WRONLY);
    file.write_all(content, std::strlen(content));
    file.close();
}
void run()
{
    const char *broken[] =
    {
        "-1\n",
        "0\n",
        "4294967295\n",
        "1junk\n",
        "",
        "123\n456\n"
    };
    for(unsigned i = 0; i < __vic::array_size(broken); i++)
    {
        write_file(pid_file_name, broken[i]);
        assert(daemon_control::control("status", pid_file_name) == 2);
    }
    ::unlink(pid_file_name);
}

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
void run_interactive()
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
        tests::run();
        if(argc == 2 && std::strcmp(argv[1], "interactive") == 0)
            tests::run_interactive();
        return 0;
    }
    catch(const std::exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }
    return 1;
}
