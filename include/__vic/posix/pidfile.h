// PID-file object
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2011

#ifndef __VIC_POSIX_PIDFILE_H
#define __VIC_POSIX_PIDFILE_H

#include<__vic/defs.h>
#include<exception>
#include<string>

namespace __vic { namespace posix {

//////////////////////////////////////////////////////////////////////////////
class pidfile : private non_copyable
{
    std::string name;
    int fd;
public:
    struct already_exists : public std::exception
    {
        const char *what() const noexcept;
    };

    explicit pidfile(std::string );
    ~pidfile();

    void create();
    void prepare_to_daemon();
    void rewrite_pid();
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
