// Not buffered low-level binary file
//
// Platform: ISO C++ 98/11 - Windows
// $Id$
//
// (c) __vic 2006

#ifndef __VIC_BIN_FILE_H
#define __VIC_BIN_FILE_H

#include<__vic/defs.h>
#include __VIC_SWAP_HEADER
#include<__vic/windows/throw_last_error.h>
#include<windows.h>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
class bin_file : private non_copyable
{
    HANDLE hFile;
    bool open_(const char * , DWORD , DWORD );
    void reset_handle() { hFile = INVALID_HANDLE_VALUE; }
public:
    // Constructor tags
    enum in_t     { in     = OPEN_EXISTING };
    enum out_t    { out    = CREATE_ALWAYS };
    enum append_t { append = OPEN_ALWAYS };

    bin_file() : hFile(INVALID_HANDLE_VALUE) {}
    bin_file(const char *fname, in_t) { open_in(fname); }
    bin_file(const char *fname, out_t) { open_out(fname); }
    bin_file(const char *fname, append_t) { open_append(fname); }
    ~bin_file() { if(is_open()) ::CloseHandle(hFile); }

#if __cpp_rvalue_references
    bin_file(bin_file &&o) noexcept : hFile(o.hFile) { o.reset_handle(); }
    bin_file &operator=(bin_file &&o) noexcept { swap(o); return *this; }
#endif

    bool open_in(const char *fname) { return open_(fname, GENERIC_READ, in); }
    bool open_out(const char *fname) { return open_(fname, GENERIC_WRITE, out); }
    bool open_append(const char * );

    size_t read_max(void * , size_t );
    size_t read_some(void * , size_t );

    void write_all(const void * , size_t );

    bool is_open() const { return hFile != INVALID_HANDLE_VALUE; }
    void close();
    bool close_nt() noexcept
    {
        bool st = ::CloseHandle(hFile);
        reset_handle();
        return st;
    }

    void swap(bin_file &o) noexcept { std::swap(hFile, o.hFile); }

    __VIC_NORETURN void throw_last_error(const char *msg)
        { windows::throw_last_error(msg); }
    void throw_if_closed(const char *msg)
        { if(!is_open()) throw_last_error(msg); }
};
//////////////////////////////////////////////////////////////////////////////

} // namespace

#endif // header guard
