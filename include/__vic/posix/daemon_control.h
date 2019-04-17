// Base class for UNIX-daemons (implements process control)
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2013

#ifndef __VIC_POSIX_DAEMON_CONTROL_H
#define __VIC_POSIX_DAEMON_CONTROL_H

#include<__vic/defs.h>
#include<__vic/posix/pidfile.h>
#include<exception>
#include<string>

namespace __vic { namespace posix {

//////////////////////////////////////////////////////////////////////////////
class daemon_control
{
    pidfile pid_file;
public:
    struct already_running : public std::exception
    {
        const char *what() const noexcept;
    };
    explicit daemon_control(std::string );

    void daemonize();

    // First arg's values: stop, kill, status
    static int control(const char * , const char * );
    static void stop_and_wait(const char * );
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
