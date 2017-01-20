// Not buffered low-level binary file
//
// Platform: ISO C++ 98/11 - POSIX
// $Id$
//
// (c) __vic 2006

#ifndef __VIC_BIN_FILE_H
#define __VIC_BIN_FILE_H

#include<__vic/defs.h>
#include<__vic/posix/file.h>
#include<__vic/throw_errno.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
class bin_file
{
    posix::file f;
public:
    // Constructor tags
    enum in_t     { in     = O_RDONLY };
    enum out_t    { out    = O_WRONLY | O_CREAT | O_TRUNC };
    enum append_t { append = O_WRONLY | O_CREAT | O_APPEND };

    bin_file() __VIC_DEFAULT_CTR
    bin_file(const char *fname, in_t) : f(fname, in) {}
    bin_file(const char *fname, out_t) : f(fname, out) {}
    bin_file(const char *fname, append_t) : f(fname, append) {}

    bool open_in(const char *fname) { return f.open(fname, in); }
    bool open_out(const char *fname) { return f.open(fname, out); }
    bool open_append(const char *fname) { return f.open(fname, append); }

    size_t read_max(void *buf, size_t n) { return f.read_max(buf, n); }
    size_t read_some(void *buf, size_t n) { return f.read_some(buf, n); }

    void write_all(const void *buf, size_t n) { f.write_all(buf, n); }

    bool is_open() const { return f.is_open(); }
    void close() { f.close(); }
    bool close_nt() noexcept { return f.close_nt(); }

    void swap(bin_file &o) noexcept { f.swap(o.f); }

    __VIC_NORETURN void throw_last_error(const char *msg) { throw_errno(msg); }
    void throw_if_closed(const char *msg)
        { if(!is_open()) throw_last_error(msg); }
};
//////////////////////////////////////////////////////////////////////////////

} // namespace

#endif // header guard
