// Not buffered low-level binary file
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2006

#ifndef __VIC_BIN_FILE_H
#define __VIC_BIN_FILE_H

#include<__vic/defs.h>
#include<__vic/io.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
class bin_file
{
    stdio_file f;
    bool open_(const char * , char );
public:
    // Constructor tags
    enum in_t     { in     = 'r' };
    enum out_t    { out    = 'w' };
    enum append_t { append = 'a' };

    bin_file() __VIC_DEFAULT_CTR
    bin_file(const char *fname, in_t) { open_in(fname); }
    bin_file(const char *fname, out_t) { open_out(fname); }
    bin_file(const char *fname, append_t) { open_append(fname); }

    bool open_in(const char *fname) { return open_(fname, in); }
    bool open_out(const char *fname) { return open_(fname, out); }
    bool open_append(const char *fname) { return open_(fname, append); }

    size_t read_max(void * , size_t );
    size_t read_some(void *buf, size_t n) { return read_max(buf, n); }

    void write_all(const void * , size_t );

    bool is_open() const { return f.is_open(); }
    void close() { f.close(); }
    bool close_nt() noexcept { return f.close_nt(); }

    void swap(bin_file &o) noexcept { f.swap(o.f); }

    __VIC_NORETURN void throw_last_error(const char * );
    void throw_if_closed(const char *msg)
        { if(!is_open()) throw_last_error(msg); }
};
//////////////////////////////////////////////////////////////////////////////

} // namespace

#endif // header guard
