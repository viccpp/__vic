// C++ interface for POSIX files-related syscalls
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2012

#ifndef __VIC_POSIX_FILE_H
#define __VIC_POSIX_FILE_H

#include<__vic/defs.h>
#include __VIC_SWAP_HEADER
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

namespace __vic { namespace posix {

//////////////////////////////////////////////////////////////////////////////
// RAII-wrapper for file descriptor
class file : private non_copyable
{
    int fd;
public:
    explicit __VIC_CONSTEXPR_FUNC file(int fd = -1) : fd(fd) {}
    file(const char *name, int flags, ::mode_t mode = 0666)
        : fd(::open(name, flags, mode)) {}
    ~file() { if(is_open()) close_nt(fd); }

#if __cpp_rvalue_references
    file(file &&o) noexcept : fd(o.fd) { o.fd = -1; }
    file &operator=(file &&o) noexcept { swap(o); return *this; }
#endif

    bool open(const char *name, int flags, ::mode_t mode = 0666)
        { fd = ::open(name, flags, mode); return is_open(); }
    void close() { close_reset(fd); }
    bool close_nt() noexcept { bool st = close_nt(fd); fd = -1; return st; }
    bool is_open() const { return fd != -1; }
    int detach() { int f = fd; fd = -1; return f; }
    void attach(int f) { fd = f; }
    void swap(file &o) noexcept { std::swap(fd, o.fd); }
    int handle() const { return fd; }
    int descriptor() const { return handle(); }

    size_t read_max(void *buf, size_t n) { return read_max(fd, buf, n); }
    size_t read_some(void *buf, size_t n) { return read_some(fd, buf, n); }
    void write_all(const void *buf, size_t n) { write_all(fd, buf, n); }
    size_t write_all_nt(const void *buf, size_t n) noexcept
        { return write_all_nt(fd, buf, n); }

    static size_t read_max(int , void * , size_t );
    static size_t read_some(int , void * , size_t );
    static void write_all(int , const void * , size_t );
    static size_t write_all_nt(int , const void * , size_t ) noexcept;
    static void close_reset(int & );
    static bool close_nt(int ) noexcept;
};
//////////////////////////////////////////////////////////////////////////////

}} // namespace

#endif // header guard
